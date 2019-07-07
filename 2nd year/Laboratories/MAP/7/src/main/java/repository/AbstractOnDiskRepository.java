package repository;

import domain.HasId;
import domain.validator.Validator;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.Paths;

abstract class AbstractOnDiskRepository<ID, E extends HasId<ID>> extends InMemoryRepository<ID, E> {
    private static Logger logger = LogManager.getLogger("file");

    String fileName;

    AbstractOnDiskRepository(Validator<E> validator, String fileName) {
        super(validator);
        this.fileName = fileName;
        createFile();
    }

    /**
     * This methods creates the file with the given fileName if it doesn't exist
     * If there is one already then it isn't overwritten
     */
    private void createFile() {
        try {
            Files.createFile(Paths.get(fileName));
            logger.info("Creating new repository file: " + fileName);
        } catch (FileAlreadyExistsException e) {
            logger.info("Using existing repository file: " + fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * This method reads data from fileName in memory
     */
    abstract void loadData();

    /**
     * This method dumps the repository to fileName, overwriting old content
     */
    abstract void dumpData();
}
