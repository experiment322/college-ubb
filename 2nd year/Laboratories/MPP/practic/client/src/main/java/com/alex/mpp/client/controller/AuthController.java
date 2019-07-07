package com.alex.mpp.client.controller;

import com.alex.mpp.client.Client;
import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.data.domain.Player;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import org.springframework.stereotype.Controller;

@Controller
public class AuthController {
    private Player player = null;

    @FXML
    private AnchorPane pane;
    @FXML
    private TextField hostField;
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;

    private void authenticatePlayer() {
        SocketManager.runWithSocket(SocketManager.getServerHost(), SocketManager.getLoginServerPort(),
                e -> Client.showAlert(Alert.AlertType.ERROR, e.toString(), ButtonType.CLOSE),
                (socket, outputStream, inputStream) -> {
                    outputStream.writeObject(usernameField.getText());
                    outputStream.writeObject(passwordField.getText());

                    player = (Player) inputStream.readObject();

                    if (player != null) {
                        Client.activatePane(Client.AppPane.MAIN);
                    } else {
                        Client.showAlert(
                                Alert.AlertType.ERROR,
                                "USERNAME & PASSWORD combination wrong!",
                                ButtonType.CLOSE
                        );
                    }
                }
        );
    }

    void invalidatePlayer() {
        player = null;
    }

    Player getPlayer() {
        return player;
    }

    @FXML
    private void initialize() {
        pane.sceneProperty().addListener((observable, oldValue, newValue) -> {
            if (oldValue != null && oldValue.getRoot() == pane) {
                passwordField.setText("");
            }
        });

        hostField.setText(SocketManager.getServerHost());
    }

    @FXML
    private void handleLoginButtonAction() {
        authenticatePlayer();
    }

    @FXML
    private void handlePasswordFieldAction() {
        authenticatePlayer();
    }
}
