package repository;

import domain.HasID;
import domain.validator.Validator;

import java.io.*;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

public abstract class AbstractFileRepository<ID, E extends HasID<ID>> extends InMemoryRepository<ID, E> implements Observer {
    private String fileName;

    /**
     * Constructor
     * Creates the repository file if it doesn't exist, or reuses it
     * Calls loadData to read the file contents
     * Observes itself to dumpData after every successful CRUD operation from base class
     *
     * @param fileName  repository file
     * @param validator entity validator
     */
    AbstractFileRepository(String fileName, Validator validator) {
        super(validator);
        this.fileName = fileName;
        try {
            Files.createFile(Paths.get(fileName));
        } catch (FileAlreadyExistsException e) {
            System.console().printf("Using existing repository file: %s\n", fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
        loadData();
        addObserver(this);
    }

    /**
     * This method reads data from fileName in memory
     * Called in constructor to initialize the repository
     */
    private void loadData() {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName))) {
            for (String line = bufferedReader.readLine(); line != null; line = bufferedReader.readLine()) {
                List<String> attributes = Arrays.asList(line.split("\\|"));
                E entity = extractEntity(attributes);
                super.save(entity);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * This method dumps the repository to fileName
     * Completely rewrites fileName
     * Called by update after every successful CRUD operation
     */
    private void dumpData() {
        try (BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(fileName, false))) {
            for (E entity : findAll()) {
                bufferedWriter.write(entity.toString());
                bufferedWriter.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * This methods creates a specialized entity from the list of attributes
     * The list of attributes has the following structure: key1=val1, key2=val2, key3=val3...
     *
     * @param attributes list of attributes as strings
     * @return the specialized entity created from the given attributes
     */
    abstract E extractEntity(List<String> attributes);

    @Override
    public void update(Observable o, Object arg) {
        if (o == this) {
            dumpData();
        }
    }
}
