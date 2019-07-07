package service;

import domain.Artist;
import repository.Repository;

import java.util.List;
import java.util.stream.Collectors;

public class ArtistService {
    private Repository<Long, Artist> repository;

    public ArtistService(Repository<Long, Artist> repository) {
        this.repository = repository;
    }

    public List<Artist> findByGenre(String genre) {
        return repository.findAll().stream()
                .filter(artist -> artist.getGenMuzical().equals(genre))
                .collect(Collectors.toList());
    }
}
