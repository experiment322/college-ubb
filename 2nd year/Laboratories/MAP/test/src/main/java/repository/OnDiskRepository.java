package repository;

import domain.HasId;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.function.Function;
import java.util.stream.Stream;

public class OnDiskRepository<ID, E extends HasId<ID>> extends InMemoryRepository<ID, E> {
    private String fileName;
    private Function<String, E> deserializer;

    public OnDiskRepository(String fileName, Function<String, E> deserializer) {
        super();
        this.fileName = fileName;
        this.deserializer = deserializer;

        loadData();
    }

    private void loadData() {
        try (Stream<String> stream = Files.lines(Paths.get(fileName))) {
            stream.forEach(line -> {
                E entity = deserializer.apply(line);
                entities.put(entity.getId(), entity);
            });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
