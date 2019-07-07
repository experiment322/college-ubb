package repository;

import domain.HasId;
import domain.validator.ValidationException;
import domain.validator.Validator;
import lombok.AllArgsConstructor;
import lombok.Data;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class InMemoryRepositoryTest {
    @Data
    @AllArgsConstructor
    class TestEntity implements HasId<Integer> {
        private Integer id;
    }

    class TestEntityValidator implements Validator<TestEntity> {
        @Override
        public void validate(TestEntity entity) throws ValidationException {
            if (entity.getId() == null || entity.getId() < 0) {
                throw new ValidationException("id is invalid (null or negative)");
            }
        }
    }

    private InMemoryRepository<Integer, TestEntity> testEntityInMemoryRepository;

    @Before
    public void setUp() {
        testEntityInMemoryRepository = new InMemoryRepository<>(new TestEntityValidator());
    }

    @Test(expected = IllegalArgumentException.class)
    public void findOneFail() {
        testEntityInMemoryRepository.findOne(null);
    }

    @Test
    public void findOne() {
        assertNull(testEntityInMemoryRepository.findOne(1));
        testEntityInMemoryRepository.save(new TestEntity(1));
        assertNotNull(testEntityInMemoryRepository.findOne(1));
    }

    @Test
    public void findAll() {
        assertFalse(testEntityInMemoryRepository.findAll().iterator().hasNext());
        testEntityInMemoryRepository.save(new TestEntity(1));
        assertTrue(testEntityInMemoryRepository.findAll().iterator().hasNext());
    }

    @Test(expected = IllegalArgumentException.class)
    public void saveFail() {
        testEntityInMemoryRepository.save(null);
    }

    @Test(expected = ValidationException.class)
    public void saveValidate() {
        testEntityInMemoryRepository.save(new TestEntity(null));
    }

    @Test
    public void save() {
        assertNull(testEntityInMemoryRepository.save(new TestEntity(1)));
        assertEquals(testEntityInMemoryRepository.save(new TestEntity(1)), new TestEntity(1));
    }

    @Test
    public void delete() {
        assertNull(testEntityInMemoryRepository.delete(1));
        testEntityInMemoryRepository.save(new TestEntity(1));
        assertNotNull(testEntityInMemoryRepository.delete(1));
    }

    @Test(expected = IllegalArgumentException.class)
    public void updateFail() {
        testEntityInMemoryRepository.update(null);
    }

    @Test(expected = ValidationException.class)
    public void updateValidate() {
        testEntityInMemoryRepository.update(new TestEntity(null));
    }

    @Test
    public void update() {
        assertNotNull(testEntityInMemoryRepository.update(new TestEntity(1)));
        testEntityInMemoryRepository.save(new TestEntity(1));
        assertNull(testEntityInMemoryRepository.update(new TestEntity(1)));
    }
}
