package utils;

import domain.HasId;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class EntityUtils {
    private static final String ENTRY_SEPARATOR;
    private static final String KEY_VALUE_DELIMITER;
    private static final String ILLEGAL_CHARACTER_PLACEHOLDER;

    static {
        ENTRY_SEPARATOR = "|";
        KEY_VALUE_DELIMITER = "=";
        ILLEGAL_CHARACTER_PLACEHOLDER = "?";
    }

    private static List<Field> getFieldsAsList(Object entity) {
        return Stream.of(entity.getClass().getDeclaredFields())
                .sorted(Comparator.comparing(Field::getName))
                .collect(Collectors.toList());
    }

    private static Map<String, Field> getFieldsAsMap(Object entity) {
        return Stream.of(entity.getClass().getDeclaredFields())
                .collect(Collectors.toMap(Field::getName, Function.identity()));
    }

    private static String sanitizeString(String string) {
        return string
                .replaceAll(Pattern.quote(ENTRY_SEPARATOR), ILLEGAL_CHARACTER_PLACEHOLDER)
                .replaceAll(Pattern.quote(KEY_VALUE_DELIMITER), ILLEGAL_CHARACTER_PLACEHOLDER);
    }

    public static String dumpString(HasId<?> entity) {
        List<Field> fields = getFieldsAsList(entity);
        List<String> entries = new ArrayList<>();

        for (Field field : fields) {
            field.setAccessible(true);
            try {
                String key = field.getName();
                String value = sanitizeString(field.get(entity).toString());
                entries.add(String.join(KEY_VALUE_DELIMITER, key, value));
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        }

        return String.join(ENTRY_SEPARATOR, entries);
    }

    public static <T extends HasId<?>> T fromString(T entity, String string) {
        Map<String, Field> fields = getFieldsAsMap(entity);
        String[] entries = string.split(Pattern.quote(ENTRY_SEPARATOR));

        for (String entry : entries) {
            String key = entry.split(Pattern.quote(KEY_VALUE_DELIMITER))[0];
            String value = entry.split(Pattern.quote(KEY_VALUE_DELIMITER))[1];
            try {
                Field field = fields.get(key);
                field.setAccessible(true);
                field.set(entity, field.getType().getConstructor(String.class).newInstance(value));
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        }

        return entity;
    }

    public static Element dumpXML(HasId<?> entity, Document document) {
        List<Field> fields = getFieldsAsList(entity);
        Element entityElement = document.createElement(entity.getClass().getSimpleName());

        for (Field field : fields) {
            field.setAccessible(true);
            try {
                String key = field.getName();
                String value = sanitizeString(field.get(entity).toString());
                Element fieldElement = document.createElement(key);
                fieldElement.appendChild(document.createTextNode(value));
                entityElement.appendChild(fieldElement);
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        }

        return entityElement;
    }

    public static <T extends HasId<?>> T fromXML(T entity, Element element) {
        Map<String, Field> fields = getFieldsAsMap(entity);
        NodeList nodeList = element.getChildNodes();

        for (int i = 0; i < nodeList.getLength(); ++i) {
            Node node = nodeList.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element fieldElement = (Element) node;
                String key = fieldElement.getTagName();
                String value = fieldElement.getTextContent();
                try {
                    Field field = fields.get(key);
                    field.setAccessible(true);
                    field.set(entity, field.getType().getConstructor(String.class).newInstance(value));
                } catch (Exception e) {
                    e.printStackTrace();
                    return null;
                }
            }
        }

        return entity;
    }

    public static <T extends HasId<?>> T clone(T source, T destination) {
        List<Field> fields = getFieldsAsList(source);

        try {
            for (Field field : fields) {
                field.setAccessible(true);
                field.set(destination, field.get(source));
            }
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }

        return destination;
    }
}
