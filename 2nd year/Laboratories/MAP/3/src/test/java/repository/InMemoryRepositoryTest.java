package repository;

import domain.BaseEntity;
import domain.validator.BaseEntityValidator;
import domain.validator.ValidationException;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class InMemoryRepositoryTest {
    private InMemoryRepository<Integer, BaseEntity> testEntityInMemoryRepository;

    @Before
    public void setUp() {
        testEntityInMemoryRepository = new InMemoryRepository<>(new BaseEntityValidator());
    }

    @Test(expected = IllegalArgumentException.class)
    public void findOneFail() {
        testEntityInMemoryRepository.findOne(null);
    }

    @Test
    public void findOne() {
        assertNull(testEntityInMemoryRepository.findOne(1));
        testEntityInMemoryRepository.save(new BaseEntity(1));
        assertNotNull(testEntityInMemoryRepository.findOne(1));
    }

    @Test
    public void findAll() {
        assertFalse(testEntityInMemoryRepository.findAll().iterator().hasNext());
        testEntityInMemoryRepository.save(new BaseEntity(1));
        assertTrue(testEntityInMemoryRepository.findAll().iterator().hasNext());
    }

    @Test(expected = IllegalArgumentException.class)
    public void saveFail() {
        testEntityInMemoryRepository.save(null);
    }

    @Test(expected = ValidationException.class)
    public void saveValidate() {
        testEntityInMemoryRepository.save(new BaseEntity(null));
    }

    @Test
    public void save() {
        assertNull(testEntityInMemoryRepository.save(new BaseEntity(1)));
        assertEquals(testEntityInMemoryRepository.save(new BaseEntity(1)), new BaseEntity(1));
    }

    @Test
    public void delete() {
        assertNull(testEntityInMemoryRepository.delete(1));
        testEntityInMemoryRepository.save(new BaseEntity(1));
        assertNotNull(testEntityInMemoryRepository.delete(1));
    }

    @Test(expected = IllegalArgumentException.class)
    public void updateFail() {
        testEntityInMemoryRepository.update(null);
    }

    @Test(expected = ValidationException.class)
    public void updateValidate() {
        testEntityInMemoryRepository.update(new BaseEntity(null));
    }

    @Test
    public void update() {
        assertNotNull(testEntityInMemoryRepository.update(new BaseEntity(1)));
        testEntityInMemoryRepository.save(new BaseEntity(1));
        assertNull(testEntityInMemoryRepository.update(new BaseEntity(1)));
    }
}
