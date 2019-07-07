package repository;

import domain.Person;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.logging.Logger;


public class PersonRepository implements IPersonRepository {
    private static final Logger LOGGER = Logger.getLogger(PersonRepository.class.getName());
    private static final String CONN_URL = "jdbc:postgresql:alex_mpp";

    public Iterable<Person> findAll() {
        Collection<Person> personCollection = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(CONN_URL)) {
            PreparedStatement statement = connection
                    .prepareStatement("select id, age, name from alex_mpp.public.person;");
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                personCollection.add(new Person(
                        resultSet.getInt("id"),
                        resultSet.getInt("age"),
                        resultSet.getString("name")
                ));
            }
        } catch (Exception e) {
            LOGGER.severe(e.getMessage());
        }
        return personCollection;
    }

    @Override
    public void delete(Integer id) {
        try (Connection connection = DriverManager.getConnection(CONN_URL)) {
            PreparedStatement statement = connection
                    .prepareStatement("delete from alex_mpp.public.person where id = ?;");
            statement.setInt(1, id);
            statement.execute();
        } catch (Exception e) {
            LOGGER.severe(e.getMessage());
        }
    }

    @Override
    public void save(Person person) {
        try (Connection connection = DriverManager.getConnection(CONN_URL)) {
            PreparedStatement statement = connection
                    .prepareStatement("insert into alex_mpp.public.person values (?, ?, ?);");
            statement.setInt(1, person.getId());
            statement.setString(2, person.getName());
            statement.setInt(3, person.getAge());
            statement.execute();
        } catch (Exception e) {
            LOGGER.severe(e.getMessage());
        }
    }

    @Override
    public void update(Person person) {
        try (Connection connection = DriverManager.getConnection(CONN_URL)) {
            PreparedStatement statement = connection
                    .prepareStatement("update alex_mpp.public.person set age = ?, name = ? where id = ?;");
            statement.setInt(1, person.getAge());
            statement.setString(2, person.getName());
            statement.setInt(3, person.getId());
            statement.execute();
        } catch (Exception e) {
            LOGGER.severe(e.getMessage());
        }
    }
}
