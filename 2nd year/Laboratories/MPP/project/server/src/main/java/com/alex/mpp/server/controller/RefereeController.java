package com.alex.mpp.server.controller;

import com.alex.mpp.data.domain.Referee;
import com.alex.mpp.data.repository.RefereeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class RefereeController {
    private final RefereeRepository refereeRepository;

    @Autowired
    public RefereeController(RefereeRepository refereeRepository) {
        this.refereeRepository = refereeRepository;
    }

    @GetMapping("/referee/all")
    public Iterable<Referee> findAllReferees() {
        return refereeRepository.findAll();
    }

    @GetMapping("/referee/{id}")
    public Referee findOneReferee(@PathVariable Integer id) {
        return refereeRepository.findOne(id);
    }

    @PostMapping("/referee")
    public Referee saveReferee(@RequestBody Referee referee) {
        refereeRepository.save(referee);
        return refereeRepository.findOne(referee.getId());
    }
}
