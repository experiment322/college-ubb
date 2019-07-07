package com.alex.mpp.data.util;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

@Service
public class JDBCManager {
    private static final Logger LOGGER = LoggerFactory.getLogger(JDBCManager.class);

    private Connection connection = null;
    private Properties properties = new Properties();

    public JDBCManager() {
        String propertiesFile = "jdbc.properties";
        InputStream inputStream = JDBCManager.class.getClassLoader().getResourceAsStream(propertiesFile);
        try {
            properties.load(inputStream);
        } catch (IOException e) {
            LOGGER.error(e.toString());
        } finally {
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (IOException e) {
                    LOGGER.error(e.toString());
                }
            }
        }
    }

    public Connection getConnection() throws SQLException {
        if (connection == null) {
            connection = DriverManager.getConnection(properties.getProperty("url"));
            LOGGER.info("Connected to database " + connection.getCatalog());
        }

        return connection;
    }
}
