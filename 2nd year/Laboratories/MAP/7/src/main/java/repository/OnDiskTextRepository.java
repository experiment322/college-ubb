package repository;

import domain.HasId;
import domain.validator.Validator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class OnDiskTextRepository<ID, E extends HasId<ID>> extends AbstractOnDiskRepository<ID, E> {
    private Function<E, String> serializer;
    private Function<String, E> deserializer;

    public OnDiskTextRepository(Validator<E> validator, String fileName, Function<E, String> serializer, Function<String, E> deserializer) {
        super(validator, fileName);
        this.serializer = serializer;
        this.deserializer = deserializer;
        loadData();
    }

    @Override
    void loadData() {
        try (Stream<String> stream = Files.lines(Paths.get(fileName))) {
            stream.forEach(line -> super.save(
                    deserializer.apply(line)
            ));
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            observeChanges(change -> dumpData());
        }
    }

    @Override
    void dumpData() {
        try {
            Files.write(
                    Paths.get(fileName),
                    StreamSupport.stream(findAll().spliterator(), false)
                            .map(entity -> serializer.apply(entity))
                            .collect(Collectors.toList())
            );
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
