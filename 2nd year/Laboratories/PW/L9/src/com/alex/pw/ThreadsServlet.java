package com.alex.pw;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

@WebServlet(name = "ThreadsServlet", urlPatterns = "")
public class ThreadsServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        try {
            Class.forName("org.mariadb.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mariadb://localhost:3306/alex", "root", "root");
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("select id, content from thread");

            ArrayList<Thread> threadList = new ArrayList<>();
            while (resultSet.next()) {
                threadList.add(new Thread(resultSet.getInt("id"), resultSet.getString("content")));
            }
            connection.close();

            request.setAttribute("threads", threadList);
            request.getRequestDispatcher("/WEB-INF/index.jsp").forward(request, response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
