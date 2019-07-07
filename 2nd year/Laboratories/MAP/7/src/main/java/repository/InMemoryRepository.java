package repository;

import domain.HasId;
import domain.validator.Validator;
import javafx.collections.FXCollections;
import javafx.collections.MapChangeListener;
import javafx.collections.ObservableMap;

/**
 * General implementation of an in-memory CRUD repository
 *
 * @param <ID> the id type used by the entities in this repository
 * @param <E>  the type of entity to save in this repository; must extend HasId
 */
public class InMemoryRepository<ID, E extends HasId<ID>> implements CrudRepository<ID, E> {
    private Validator<E> validator;
    private ObservableMap<ID, E> entities;

    /**
     * Constructor
     *
     * @param validator validator instance to check entities in before save/update
     */
    public InMemoryRepository(Validator<E> validator) {
        this.entities = FXCollections.observableHashMap();
        this.validator = validator;
    }

    @Override
    public void observeChanges(MapChangeListener<ID, E> handler) {
        entities.addListener(handler);
    }

    /**
     * Get the entity with the given id from the repository
     *
     * @param id the id of the entity to be returned;
     *           id must not be null
     * @return the entity with the given id if found; null otherwise
     */
    @Override
    public E findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id must be not null");
        }
        return entities.get(id);
    }

    /**
     * Get all entities in the repository
     *
     * @return an iterable over the repository contents
     */
    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    /**
     * Validate and save an entity in the repository
     *
     * @param entity entity must be not null
     * @return null if successful; the given entity otherwise
     */
    @Override
    public E save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity must be not null");
        }
        validator.validate(entity);
        E result = entity;
        if (entities.get(entity.getId()) == null) {
            entities.put(entity.getId(), entity);
            result = null;
        }
        return result;
    }

    /**
     * Update one entity in the repository
     *
     * @param entity entity must not be null
     * @return null if successful; the given entity otherwise
     */
    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity must be not null!");
        }
        validator.validate(entity);
        E result = entity;
        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);
            result = null;
        }
        return result;
    }

    /**
     * Remove one entity from the repository
     *
     * @param id id must be not null
     * @return the removed entity if successful; null otherwise
     */
    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id must be not null");
        }
        E result = null;
        if (entities.get(id) != null) {
            result = entities.remove(id);
        }
        return result;
    }
}
