package com.alex.mpp.server.service;

import com.alex.mpp.common.service.GameService;
import com.alex.mpp.data.domain.Game;
import com.alex.mpp.data.repository.GameRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class RemoteGameService implements GameService {
    private final SocketLoginService loginService;
    private final GameRepository gameRepository;

    @Autowired
    public RemoteGameService(SocketLoginService loginService, GameRepository gameRepository) {
        this.loginService = loginService;
        this.gameRepository = gameRepository;
    }

    @Override
    public Game getGameById(Integer id) {
        if (loginService.isRmiClientUnauthorized()) {
            throw new SecurityException();
        }

        return gameRepository.findById(id).orElse(null);
    }
}
