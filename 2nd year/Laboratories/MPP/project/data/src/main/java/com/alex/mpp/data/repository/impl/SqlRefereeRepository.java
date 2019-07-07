package com.alex.mpp.data.repository.impl;

import com.alex.mpp.data.domain.Referee;
import com.alex.mpp.data.repository.RefereeRepository;
import com.alex.mpp.data.util.JDBCManager;
import com.axiomalaska.jdbc.NamedParameterPreparedStatement;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

@Repository
public class SqlRefereeRepository implements RefereeRepository {
    private static final Logger LOGGER = LoggerFactory.getLogger(SqlRefereeRepository.class);

    private Connection connection;

    @Autowired
    public SqlRefereeRepository(JDBCManager jdbcManager) throws SQLException {
        this.connection = jdbcManager.getConnection();
    }

    @Override
    public Referee findOne(Integer id) {
        final String sql_query = "select id, game_id, name, username, password from alex_mpp.public.referee where id = :id";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("id", id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return new Referee(
                        resultSet.getInt("id"),
                        resultSet.getInt("game_id"),
                        resultSet.getString("name"),
                        resultSet.getString("username"),
                        resultSet.getString("password")
                );
            }
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public Iterable<Referee> findAll() {
        final String sql_query = "select id, game_id, name, username, password from alex_mpp.public.referee";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);

            ArrayList<Referee> referees = new ArrayList<>();
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                referees.add(new Referee(
                        resultSet.getInt("id"),
                        resultSet.getInt("game_id"),
                        resultSet.getString("name"),
                        resultSet.getString("username"),
                        resultSet.getString("password")
                ));
            }

            return referees;
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public void save(Referee referee) {
        final String sql_query = "insert into alex_mpp.public.referee values (default, :name, :game_id, :username, :password)";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("game_id", referee.getGameId());
            statement.setString("name", referee.getName());
            statement.setString("username", referee.getUsername());
            statement.setString("password", referee.getPassword());

            statement.execute();
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void update(Referee referee) {
        final String sql_query = "update alex_mpp.public.referee set game_id = :game_id, name = :name, username = :username, password = :password where id = :id";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("game_id", referee.getGameId());
            statement.setString("name", referee.getName());
            statement.setString("username", referee.getUsername());
            statement.setString("password", referee.getPassword());
            statement.setInt("id", referee.getId());

            statement.execute();
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void delete(Integer id) {
        final String sql_query = "delete from alex_mpp.public.referee where id = :id";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("id", id);

            statement.execute();
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }
}
