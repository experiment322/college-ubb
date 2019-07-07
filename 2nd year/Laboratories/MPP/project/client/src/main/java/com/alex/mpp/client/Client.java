package com.alex.mpp.client;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;

import java.util.EnumMap;

@SpringBootApplication(scanBasePackages = {"com.alex.mpp.client"})
public class Client extends Application {
    public enum AppPane {AUTH, MAIN}

    private static Scene appScene;
    private static EnumMap<AppPane, Pane> appPaneMap;

    private static ApplicationContext appContext;

    private static Pane loadFXML(String location) throws Exception {
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setControllerFactory(appContext::getBean);
        fxmlLoader.setLocation(Client.class.getResource(location));

        return fxmlLoader.load();
    }

    public static void activatePane(AppPane appPane) {
        Client.appScene.setRoot(appPaneMap.get(appPane));
    }

    public static void showAlert(Alert.AlertType type, String content, ButtonType... buttons) {
        Alert alert = new Alert(type, content, buttons);
        alert.setResizable(true);
        alert.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void init() {
        appScene = new Scene(new Pane());
        appPaneMap = new EnumMap<>(AppPane.class);
        appContext = SpringApplication.run(Client.class);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        appPaneMap.put(AppPane.AUTH, loadFXML("/fxml/auth_pane.fxml"));
        appPaneMap.put(AppPane.MAIN, loadFXML("/fxml/main_pane.fxml"));

        activatePane(AppPane.AUTH);

        primaryStage.setTitle("Triathlon Manager Pro");
        primaryStage.setScene(appScene);
        primaryStage.show();
    }
}
