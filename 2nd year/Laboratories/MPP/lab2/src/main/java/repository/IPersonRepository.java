package repository;

import domain.Person;

public interface IPersonRepository {
    Iterable<Person> findAll();

    void delete(Integer id);

    void save(Person person);

    void update(Person person);
}
