package repository;

import domain.HasId;
import domain.validator.ValidationException;
import javafx.collections.MapChangeListener;

/**
 * CRUD operations repository interface
 *
 * @param <ID> - type E must have an attribute of type ID
 * @param <E>  -  type of entities saved in repository
 */
public interface CrudRepository<ID, E extends HasId<ID>> {
    /**
     * @param id -the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     * or null - if there is no entity with the given id
     * @throws IllegalArgumentException if id is null.
     */
    E findOne(ID id) throws IllegalArgumentException;

    /**
     * @return all entities
     */
    Iterable<E> findAll();

    /**
     * @param entity entity must be not null
     * @return null- if the given entity is saved
     * otherwise returns the entity (id already exists)
     * @throws ValidationException      if the entity is not valid
     * @throws IllegalArgumentException if the given entity is null.     *
     */
    E save(E entity) throws ValidationException, IllegalArgumentException;

    /**
     * @param entity entity must not be null
     * @return null - if the entity is updated,
     * otherwise  returns the entity  - (e.g id does not exist).
     * @throws IllegalArgumentException if the given entity is null.
     * @throws ValidationException      if the entity is not valid.
     */
    E update(E entity) throws IllegalArgumentException, ValidationException;

    /**
     * removes the entity with the specified id
     *
     * @param id id must be not null
     * @return the removed entity or null if there is no entity with the given id
     * @throws IllegalArgumentException if the given id is null.
     */
    E delete(ID id) throws IllegalArgumentException;

    /**
     * Override this in subclass if you want to implement observer pattern on the repository
     * @param handler function receiving repository change
     */
    default void observeChanges(MapChangeListener<ID, E> handler) {
    }
}
