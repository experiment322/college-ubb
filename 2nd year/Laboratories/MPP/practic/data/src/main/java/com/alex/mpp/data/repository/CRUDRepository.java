package com.alex.mpp.data.repository;

public interface CRUDRepository<ID, T> {
    T findOne(ID id);

    Iterable<T> findAll();

    void save(T entity);

    void update(T entity);

    void delete(ID id);
}
