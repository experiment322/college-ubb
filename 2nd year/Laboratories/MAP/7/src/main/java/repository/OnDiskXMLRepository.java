package repository;

import domain.HasId;
import domain.validator.Validator;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.stream.StreamSupport;

public class OnDiskXMLRepository<ID, E extends HasId<ID>> extends AbstractOnDiskRepository<ID, E> {
    private BiFunction<E, Document, Element> serializer;
    private Function<Element, E> deserializer;

    public OnDiskXMLRepository(Validator<E> validator, String fileName, BiFunction<E, Document, Element> serializer, Function<Element, E> deserializer) {
        super(validator, fileName);
        this.serializer = serializer;
        this.deserializer = deserializer;
        loadData();
    }

    @Override
    void loadData() {
        try {
            if (Files.lines(Paths.get(fileName)).count() == 0) {
                return;
            }
            Document document = DocumentBuilderFactory.newInstance()
                    .newDocumentBuilder()
                    .parse(Files.newInputStream(Paths.get(fileName)));
            NodeList nodeList = document.getDocumentElement().getChildNodes();
            for (int i = 0; i < nodeList.getLength(); ++i) {
                Node node = nodeList.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;
                    super.save(
                            deserializer.apply(element)
                    );
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            observeChanges(change -> dumpData());
        }
    }

    @Override
    void dumpData() {
        try {
            Document document = DocumentBuilderFactory.newInstance()
                    .newDocumentBuilder()
                    .newDocument();
            document.appendChild(document.createElement("data"));
            StreamSupport.stream(findAll().spliterator(), false)
                    .forEach(entity -> document.getDocumentElement().appendChild(
                            serializer.apply(entity, document)
                    ));
            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty("indent", "yes");
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
            DOMSource domSource = new DOMSource(document);
            StreamResult streamResult = new StreamResult(Files.newOutputStream(Paths.get(fileName)));
            transformer.transform(domSource, streamResult);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
