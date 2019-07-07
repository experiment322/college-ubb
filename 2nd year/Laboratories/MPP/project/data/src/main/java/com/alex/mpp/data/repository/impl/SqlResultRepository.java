package com.alex.mpp.data.repository.impl;

import com.alex.mpp.data.domain.Result;
import com.alex.mpp.data.repository.ResultRepository;
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
public class SqlResultRepository implements ResultRepository {
    private static final Logger LOGGER = LoggerFactory.getLogger(SqlResultRepository.class);

    private Connection connection;

    @Autowired
    public SqlResultRepository(JDBCManager jdbcManager) throws SQLException {
        this.connection = jdbcManager.getConnection();
    }

    @Override
    public Result findOne(Integer id) {
        final String sql_query = "select id, game_id, athlete_id, value from alex_mpp.public.result where id = :id";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("id", id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return new Result(
                        resultSet.getInt("id"),
                        resultSet.getInt("game_id"),
                        resultSet.getInt("athlete_id"),
                        resultSet.getFloat("value")
                );
            }
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public Iterable<Result> findAll() {
        final String sql_query = "select id, game_id, athlete_id, value from alex_mpp.public.result";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);

            ArrayList<Result> results = new ArrayList<>();
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                results.add(new Result(
                        resultSet.getInt("id"),
                        resultSet.getInt("game_id"),
                        resultSet.getInt("athlete_id"),
                        resultSet.getFloat("value")
                ));
            }

            return results;
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public void save(Result result) {
        final String sql_query = "insert into alex_mpp.public.result values (default, :game_id, :athlete_id, :value)";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("game_id", result.getGameId());
            statement.setInt("athlete_id", result.getAthleteId());
            statement.setFloat("value", result.getValue());

            statement.execute();
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void update(Result result) {
        final String sql_query = "update alex_mpp.public.result set game_id = :game_id, athlete_id = :athlete_id, value = :value where id = :id";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("game_id", result.getGameId());
            statement.setInt("athlete_id", result.getAthleteId());
            statement.setFloat("value", result.getValue());
            statement.setInt("id", result.getId());

            statement.execute();
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void delete(Integer id) {
        final String sql_query = "delete from alex_mpp.public.result where id = :id";
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
