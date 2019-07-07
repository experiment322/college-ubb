package com.alex.mpp.data.mapper;

import com.alex.mpp.data.domain.GameRound;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Service;

import java.sql.ResultSet;
import java.sql.SQLException;

@Service
public class GameRoundMapper implements RowMapper<GameRound> {
    @Override
    public GameRound mapRow(ResultSet rs, int rowNum) throws SQLException {
        return new GameRound(
                rs.getInt("game_id"),
                rs.getInt("round_number"),
                rs.getInt("player_steps")
        );
    }
}
