package repository;

import domain.HasID;
import domain.validator.Validator;

import java.io.*;
import java.util.Arrays;
import java.util.List;

public abstract class AbstractFileRepository<ID, E extends HasID<ID>> extends InMemoryRepository<ID, E> {
    private String fileName;

    AbstractFileRepository(String fileName, Validator validator) {
        super(validator);
        this.fileName = fileName;
        loadData();
    }

    private void loadData() {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = br.readLine()) != null) {
                List<String> attrs = Arrays.asList(line.split("\\|"));
                E e = extractEntity(attrs);
                super.save(e);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    abstract E extractEntity(List<String> attributes);

    @Override
    public E save(E entity) {
        E e = super.save(entity);
        if (e == null) {
            writeToFile(entity);
        }
        return e;

    }

    private void writeToFile(E entity) {
        try (BufferedWriter bW = new BufferedWriter(new FileWriter(fileName, true))) {
            bW.write(entity.toString());
            bW.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
