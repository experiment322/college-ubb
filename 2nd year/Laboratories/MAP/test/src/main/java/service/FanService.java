package service;

import domain.Fan;
import repository.Repository;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class FanService {
    private Repository<Long, Fan> repository;

    public FanService(Repository<Long, Fan> repository) {
        this.repository = repository;
    }

    public List<Fan> findAllSortedByName() {
        return repository.findAll().stream()
                .sorted(Comparator.comparing(Fan::getNume))
                .collect(Collectors.toList());
    }
}
