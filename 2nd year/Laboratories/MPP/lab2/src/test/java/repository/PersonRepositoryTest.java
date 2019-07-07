package repository;

import domain.Person;
import org.junit.Before;
import org.junit.Test;

import java.util.Optional;
import java.util.stream.StreamSupport;

import static org.junit.Assert.*;

public class PersonRepositoryTest {
    private Person person;
    private PersonRepository repository;

    @Before
    public void setUp() {
        person = new Person(0, 0, "test " + System.currentTimeMillis());
        repository = new PersonRepository();

        person.setId(StreamSupport.stream(repository.findAll().spliterator(), false)
                .mapToInt(Person::getId)
                .max()
                .orElse(0) + 1);
    }

    private Optional<Person> findTestPerson() {
        return StreamSupport.stream(repository.findAll().spliterator(), false)
                .filter(entity -> entity.getId().equals(person.getId()))
                .findFirst();
    }

    @Test
    public void testCRUD() {
        repository.save(person);
        assertTrue(findTestPerson().isPresent());

        String updatedName = "test " + System.currentTimeMillis();
        repository.update(new Person(person.getId(), person.getAge(), updatedName));
        findTestPerson().ifPresent(updatedPerson -> assertEquals(updatedPerson.getName(), updatedName));

        repository.delete(person.getId());
        assertFalse(findTestPerson().isPresent());
    }
}