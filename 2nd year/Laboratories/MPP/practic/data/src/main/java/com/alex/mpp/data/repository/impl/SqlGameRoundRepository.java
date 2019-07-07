package com.alex.mpp.data.repository.impl;

import com.alex.mpp.data.domain.GameRound;
import com.alex.mpp.data.mapper.GameRoundMapper;
import com.alex.mpp.data.repository.GameRoundRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcTemplate;
import org.springframework.stereotype.Repository;
import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.util.List;
import java.util.Map;

@Repository
public class SqlGameRoundRepository implements GameRoundRepository {
    private static final Logger LOGGER = LoggerFactory.getLogger(SqlGameRoundRepository.class);

    private final GameRoundMapper gameRoundMapper;
    private final NamedParameterJdbcTemplate jdbcTemplate;

    @Autowired
    public SqlGameRoundRepository(GameRoundMapper gameRoundMapper, NamedParameterJdbcTemplate jdbcTemplate) {
        this.gameRoundMapper = gameRoundMapper;
        this.jdbcTemplate = jdbcTemplate;
    }

    @Override
    public GameRound findOne(Map.Entry<Integer, Integer> id) {
        try {
            List<GameRound> gameRounds = jdbcTemplate.query(
                    "select game_id, round_number, player_steps from alex_mpp_exam.public.game_round where game_id = :game_id and round_number = :round_number",
                    new MapSqlParameterSource()
                            .addValue("game_id", id.getKey())
                            .addValue("round_number", id.getValue()),
                    gameRoundMapper
            );

            if (gameRounds.size() == 1) {
                return gameRounds.get(0);
            }
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public Iterable<GameRound> findAll() {
        try {
            return jdbcTemplate.query(
                    "select game_id, round_number, player_steps from alex_mpp_exam.public.game_round",
                    gameRoundMapper
            );
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public void save(GameRound gameRound) {
        try {
            jdbcTemplate.update(
                    "insert into alex_mpp_exam.public.game_round values (:game_id, :round_number, :player_steps)",
                    new MapSqlParameterSource()
                            .addValue("game_id", gameRound.getGameId())
                            .addValue("round_number", gameRound.getRoundNumber())
                            .addValue("player_steps", gameRound.getPlayerSteps())
            );
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void update(GameRound gameRound) {
        throw new NotImplementedException();
    }

    @Override
    public void delete(Map.Entry<Integer, Integer> id) {
        try {
            jdbcTemplate.update(
                    "delete from alex_mpp_exam.public.game_round where game_id = :game_id and round_number = :round_number",
                    new MapSqlParameterSource()
                            .addValue("game_id", id.getKey())
                            .addValue("round_number", id.getValue())
            );
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }
}
