package ui.gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import service.MarkService;
import service.StudentService;
import service.TaskService;
import ui.UI;

public class MainGUI extends Application implements UI {
    private static MarkService markService;
    private static TaskService taskService;
    private static StudentService studentService;
    private static MainGUI mainGUI;

    public static MainGUI getInstance(MarkService markService, TaskService taskService, StudentService studentService) {
        if (mainGUI == null) {
            mainGUI = new MainGUI();
            MainGUI.markService = markService;
            MainGUI.taskService = taskService;
            MainGUI.studentService = studentService;
        }
        return mainGUI;
    }

    public static MarkService getMarkService() {
        return markService;
    }

    public static TaskService getTaskService() {
        return taskService;
    }

    public static StudentService getStudentService() {
        return studentService;
    }

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("main_layout.fxml"));
        Scene scene = new Scene(root, 800, 600);

        primaryStage.setMaximized(true);
        primaryStage.setTitle("UTM XP");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    @Override
    public void run() {
        main(null);
    }
}
