package ui.gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MainGUI extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("./main.fxml"));
        Scene scene = new Scene(root, 300, 275);

        primaryStage.setTitle("Main GUI");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
