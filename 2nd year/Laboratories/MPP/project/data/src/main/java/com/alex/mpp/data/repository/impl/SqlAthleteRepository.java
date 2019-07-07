package com.alex.mpp.data.repository.impl;

import com.alex.mpp.data.domain.Athlete;
import com.alex.mpp.data.repository.AthleteRepository;
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
public class SqlAthleteRepository implements AthleteRepository {
    private static final Logger LOGGER = LoggerFactory.getLogger(SqlAthleteRepository.class);

    private Connection connection;

    @Autowired
    public SqlAthleteRepository(JDBCManager jdbcManager) throws SQLException {
        this.connection = jdbcManager.getConnection();
    }

    @Override
    public Athlete findOne(Integer id) {
        final String sql_query = "select id, name from alex_mpp.public.athlete where id = :id";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setInt("id", id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return new Athlete(
                        resultSet.getInt("id"),
                        resultSet.getString("name")
                );
            }
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public Iterable<Athlete> findAll() {
        final String sql_query = "select id, name from alex_mpp.public.athlete";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);

            ArrayList<Athlete> athletes = new ArrayList<>();
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                athletes.add(new Athlete(
                        resultSet.getInt("id"),
                        resultSet.getString("name")
                ));
            }

            return athletes;
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }

        return null;
    }

    @Override
    public void save(Athlete athlete) {
        final String sql_query = "insert into alex_mpp.public.athlete values (default, :name)";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setString("name", athlete.getName());

            statement.execute();
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void update(Athlete athlete) {
        final String sql_query = "update alex_mpp.public.athlete set name = :name where id = :id";
        LOGGER.info(sql_query);

        try {
            NamedParameterPreparedStatement statement = NamedParameterPreparedStatement
                    .createNamedParameterPreparedStatement(connection, sql_query);
            statement.setString("name", athlete.getName());
            statement.setInt("id", athlete.getId());

            statement.execute();
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    @Override
    public void delete(Integer id) {
        final String sql_query = "delete from alex_mpp.public.athlete where id = :id";
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
