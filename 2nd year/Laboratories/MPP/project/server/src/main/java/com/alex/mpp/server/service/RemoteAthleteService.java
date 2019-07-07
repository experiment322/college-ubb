package com.alex.mpp.server.service;

import com.alex.mpp.common.service.AthleteService;
import com.alex.mpp.data.domain.Athlete;
import com.alex.mpp.data.domain.Result;
import com.alex.mpp.data.repository.AthleteRepository;
import com.alex.mpp.data.repository.ResultRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Service
public class RemoteAthleteService implements AthleteService {
    private final SocketLoginService loginService;
    private final ResultRepository resultRepository;
    private final AthleteRepository athleteRepository;

    @Autowired
    public RemoteAthleteService(SocketLoginService loginService,
                                ResultRepository resultRepository,
                                AthleteRepository athleteRepository) {
        this.loginService = loginService;
        this.resultRepository = resultRepository;
        this.athleteRepository = athleteRepository;
    }

    @Override
    public Collection<Athlete> getAthletes() {
        if (loginService.isRmiClientUnauthorized()) {
            throw new SecurityException();
        }

        return StreamSupport
                .stream(athleteRepository.findAll().spliterator(), false)
                .collect(Collectors.toList());
    }

    @Override
    public Map<String, Float> getAthletesTotalPoints() {
        if (loginService.isRmiClientUnauthorized()) {
            throw new SecurityException();
        }

        Map<String, Float> athleteResultMap = new HashMap<>();
        for (Result result : resultRepository.findAll()) {
            Athlete athlete = athleteRepository.findOne(result.getAthleteId());
            athleteResultMap.compute(athlete.getName(), (k, v) -> (v == null ? 0 : v) + result.getValue());
        }

        return athleteResultMap;
    }
}
