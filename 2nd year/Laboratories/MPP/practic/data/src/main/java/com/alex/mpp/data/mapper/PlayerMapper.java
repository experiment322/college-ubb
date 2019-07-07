package com.alex.mpp.data.mapper;

import com.alex.mpp.data.domain.Player;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Service;

import java.sql.ResultSet;
import java.sql.SQLException;

@Service
public class PlayerMapper implements RowMapper<Player> {
    @Override
    public Player mapRow(ResultSet rs, int rowNum) throws SQLException {
        return new Player(
                rs.getInt("id"),
                rs.getString("username"),
                rs.getString("password")
        );
    }
}
