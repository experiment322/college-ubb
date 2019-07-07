package com.alex.mpp.client.controller;

import com.alex.mpp.client.Client;
import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.data.domain.Referee;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import org.springframework.stereotype.Controller;

@Controller
public class AuthController {
    private Referee referee = null;

    @FXML
    private AnchorPane pane;
    @FXML
    private TextField hostField;
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;

    private void authenticateReferee() {
        SocketManager.runWithSocket(SocketManager.getServerHost(), SocketManager.getLoginServerPort(),
                e -> Client.showAlert(Alert.AlertType.ERROR, e.toString(), ButtonType.CLOSE),
                (socket, outputStream, inputStream) -> {
                    outputStream.writeObject(usernameField.getText());
                    outputStream.writeObject(passwordField.getText());

                    referee = (Referee) inputStream.readObject();

                    if (referee != null) {
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

    void invalidateReferee() {
        referee = null;
    }

    Referee getReferee() {
        return referee;
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
        authenticateReferee();
    }

    @FXML
    private void handlePasswordFieldAction() {
        authenticateReferee();
    }
}
