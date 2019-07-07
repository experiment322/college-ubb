package com.alex.mpp.data.repository.impl;

import com.alex.mpp.data.domain.Player;
import com.alex.mpp.data.mapper.PlayerMapper;
import com.alex.mpp.data.repository.PlayerRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public class SqlPlayerRepository implements PlayerRepository {
    private static final Logger LOGGER = LoggerFactory.getLogger(SqlPlayerRepository.class);

    private final PlayerMapper playerMapper;
    private final NamedParameterJdbcTemplate jdbcTemplate;

    @Autowired
    public SqlPlayerRepository(PlayerMapper playerMapper, NamedParameterJdbcTemplate jdbcTemplate) {
        this.playerMapper = playerMapper;
        this.jdbcTemplate = jdbcTemplate;
    }

    @Override
    public Player findOne(Integer id) {
        try {
            List<Player> players = jdbcTemplate.query(
                    "select id, username, password from alex_mpp_exam.public.player where id = :id",
                    new MapSqlParameterSource()
                            .addValue("id", id),
                    playerMapper
            );

            if (players.size() == 1) {
                return players.get(0);
            }
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public Iterable<Player> findAll() {
        try {
            return jdbcTemplate.query(
                    "select id, username, password from alex_mpp_exam.public.player",
                    playerMapper
            );
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public void save(Player player) {
        try {
            jdbcTemplate.update(
                    "insert into alex_mpp_exam.public.player values (default, :username, :password)",
                    new MapSqlParameterSource()
                            .addValue("username", player.getUsername())
                            .addValue("password", player.getPassword())
            );
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void update(Player player) {
        try {
            jdbcTemplate.update(
                    "update alex_mpp_exam.public.player set username = :username, password = :password where id = :id",
                    new MapSqlParameterSource()
                            .addValue("id", player.getId())
                            .addValue("username", player.getUsername())
                            .addValue("password", player.getPassword())
            );
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void delete(Integer id) {
        try {
            jdbcTemplate.update(
                    "delete from alex_mpp_exam.public.player where id = :id",
                    new MapSqlParameterSource()
                            .addValue("id", id)
            );
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }
}
