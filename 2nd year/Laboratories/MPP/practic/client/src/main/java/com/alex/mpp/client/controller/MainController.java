package com.alex.mpp.client.controller;

import com.alex.mpp.client.Client;
import com.alex.mpp.common.util.SocketManager;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

@Controller
public class MainController {
    private final AuthController authController;
    private final BlockingQueue<String> cmd = new LinkedBlockingDeque<>();
    private final BlockingQueue<String> res = new LinkedBlockingDeque<>();

    @FXML
    private AnchorPane pane;
    @FXML
    private Button rollButton;
    @FXML
    private Button playButton;
    @FXML
    private TextField rivalField;
    @FXML
    private TextField roundField;
    @FXML
    private Label gamePathLabel;

    @Autowired
    public MainController(AuthController authController) {
        this.authController = authController;
    }

    private void startMessageHandler() {
        Thread thread = new Thread(() ->
                SocketManager.runWithSocket(SocketManager.getServerHost(), SocketManager.getMessagingServerPort(),
                        e -> Client.showAlert(Alert.AlertType.ERROR, e.toString(), ButtonType.CLOSE),
                        (socket, outputStream, inputStream) -> {
                            new Thread(() -> {
                                boolean running = true;
                                while (running) {
                                    try {
                                        String command = res.take();
                                        String type = command.split(" ")[0];
                                        System.out.println(command);
                                        switch (type) {
                                            case "game":
                                                String path = command.split(" ")[1];
                                                String rival = command.split(" ")[2];
                                                gamePathLabel.setText(path);
                                                rivalField.setText(rival);
                                                break;
                                            default:
                                                running = false;
                                                break;
                                        }
                                    } catch (InterruptedException e) {
                                        break;
                                    }
                                }
                            }).start();

                            while (true) {
                                try {
                                    outputStream.writeObject(cmd.take());
                                    System.out.println("hy");
                                } catch (InterruptedException e) {
                                    break;
                                }
                            }
                        }
                ));
        thread.setDaemon(true);
        thread.start();
    }

    @FXML
    private void initialize() {
        pane.sceneProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null && newValue.getRoot() == pane) {
                rivalField.setText("");
                roundField.setText("?");
                gamePathLabel.setText("");
                rollButton.setDisable(true);
                playButton.setDisable(false);
            }
        });
        startMessageHandler();
    }

    @FXML
    private void handleExitButtonAction() {
        Client.activatePane(Client.AppPane.AUTH);
        authController.invalidatePlayer();
    }

    @FXML
    private void handlePlayButtonAction() {
        try {
            cmd.put("play " + authController.getPlayer().getId());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void handleRollButtonAction() {
    }
}
