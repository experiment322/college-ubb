package com.alex.mpp.server.controller;

import com.alex.mpp.data.domain.Game;
import com.alex.mpp.data.domain.GameRound;
import com.alex.mpp.data.repository.GameRepository;
import com.alex.mpp.data.repository.GameRoundRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;

@RestController
public class PlayerGameController {
    private final GameRepository gameRepository;
    private final GameRoundRepository gameRoundRepository;

    @Autowired
    public PlayerGameController(GameRepository gameRepository, GameRoundRepository gameRoundRepository) {
        this.gameRepository = gameRepository;
        this.gameRoundRepository = gameRoundRepository;
    }

    @GetMapping("/game/{gameId}/player/{playerId}")
    public Iterable<GameRound> findAllReferees(@PathVariable Integer gameId, @PathVariable Integer playerId) {
        Game game = gameRepository.findById(gameId).orElse(null);
        if (game == null) return null;

        List<GameRound> gameRounds = new ArrayList<>();
        int start = game.getPlayer1Id().equals(playerId) ? 1 : 2;
        for (int i = start; i < 7; i += 2) {
            gameRounds.add(gameRoundRepository.findOne(new AbstractMap.SimpleEntry<>(gameId, i)));
        }
        return gameRounds;
    }
}
