package repository;

import domain.HasId;

import java.util.Collection;

public interface Repository<ID, E extends HasId<ID>> {

    Collection<E> findAll();

    E findOne(ID id) throws IllegalArgumentException;
}
