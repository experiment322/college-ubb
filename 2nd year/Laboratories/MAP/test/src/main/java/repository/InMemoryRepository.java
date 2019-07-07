package repository;

import domain.HasId;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends HasId<ID>> implements Repository<ID, E> {
    Map<ID, E> entities;

    InMemoryRepository() {
        this.entities = new HashMap<>();
    }

    @Override
    public Collection<E> findAll() {
        return entities.values();
    }

    @Override
    public E findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id must be not null");
        }
        return entities.get(id);
    }
}
