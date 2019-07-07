package com.alex.mpp.server.service;

import com.alex.mpp.common.service.ResultService;
import com.alex.mpp.data.domain.Result;
import com.alex.mpp.data.repository.ResultRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Service
public class RemoteResultService implements ResultService {
    private final SocketLoginService loginService;
    private final SocketNotifierService notifierService;
    private final ResultRepository resultRepository;

    @Autowired
    public RemoteResultService(SocketLoginService loginService,
                               SocketNotifierService notifierService,
                               ResultRepository resultRepository) {
        this.loginService = loginService;
        this.notifierService = notifierService;
        this.resultRepository = resultRepository;
    }

    @Override
    public Collection<Result> getResultsForGame(Integer gameId) {
        if (loginService.isRmiClientUnauthorized()) {
            throw new SecurityException();
        }

        return StreamSupport
                .stream(resultRepository.findAll().spliterator(), false)
                .filter(result -> result.getGameId().equals(gameId))
                .collect(Collectors.toList());
    }

    @Override
    public void setResult(Integer athleteId, Integer gameId, Float value) {
        Result result = StreamSupport.stream(resultRepository.findAll().spliterator(), false)
                .filter(r -> r.getAthleteId().equals(athleteId) && r.getGameId().equals(gameId))
                .findFirst()
                .orElse(null);

        if (result != null) {
            result.setValue(value);
            resultRepository.update(result);
        } else {
            resultRepository.save(new Result(0, gameId, athleteId, value));
        }

        notifierService.notifyAllClients();
    }
}
