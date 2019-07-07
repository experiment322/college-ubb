package com.alex.mpp.server.service;

import com.alex.mpp.common.service.RefereeService;
import com.alex.mpp.data.domain.Referee;
import com.alex.mpp.data.repository.RefereeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class LocalRefereeService implements RefereeService {
    private final RefereeRepository refereeRepository;

    @Autowired
    public LocalRefereeService(RefereeRepository refereeRepository) {
        this.refereeRepository = refereeRepository;
    }

    @Override
    public Referee authenticate(String username, String password) {
        for (Referee referee : refereeRepository.findAll()) {
            if (referee.getUsername().equals(username) &&
                    referee.getPassword().equals(password)) {
                referee.setPassword("");
                return referee;
            }
        }

        return null;
    }
}
