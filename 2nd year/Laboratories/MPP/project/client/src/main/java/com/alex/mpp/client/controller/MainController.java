package com.alex.mpp.client.controller;

import com.alex.mpp.client.Client;
import com.alex.mpp.client.model.AthleteGameResult;
import com.alex.mpp.common.service.AthleteService;
import com.alex.mpp.common.service.GameService;
import com.alex.mpp.common.service.ResultService;
import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.data.domain.Athlete;
import com.alex.mpp.data.domain.Game;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.SortedList;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.util.StringConverter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;

import java.util.Comparator;
import java.util.Map;
import java.util.stream.Collectors;

@Controller
public class MainController {
    private final AuthController authController;
    private final AthleteService athleteService;
    private final ResultService resultService;
    private final GameService gameService;

    private Game game = null;
    private ObservableList<Athlete> athletes = FXCollections.observableArrayList();
    private ObservableList<AthleteGameResult> gameResults = FXCollections.observableArrayList();
    private ObservableList<Map.Entry<String, Float>> athletesResults = FXCollections.observableArrayList();

    @FXML
    private AnchorPane pane;
    @FXML
    private TextField refereeField;
    @FXML
    private TextField gameField;
    @FXML
    private ChoiceBox<Athlete> athletePicker;
    @FXML
    private TextField pointsField;
    @FXML
    private ListView<Map.Entry<String, Float>> athletesResultsList;
    @FXML
    private TableView<AthleteGameResult> gameResultsTable;
    @FXML
    private TableColumn<AthleteGameResult, String> gameResultsAthleteColumn;
    @FXML
    private TableColumn<AthleteGameResult, String> gameResultsPointsColumn;

    @Autowired
    public MainController(AuthController authController,
                          AthleteService athleteService,
                          ResultService resultService,
                          GameService gameService) {
        this.authController = authController;
        this.athleteService = athleteService;
        this.resultService = resultService;
        this.gameService = gameService;
    }

    private void invalidateData() {
        athletesResults.clear();
        gameResults.clear();
        athletes.clear();
        game = null;
    }

    private synchronized void initializeData() {
        Scene scene = pane.sceneProperty().get();
        if (scene != null && scene.getRoot() != pane) {
            return;
        }

        game = gameService.getGameById(authController.getReferee().getGameId());
        athletes.setAll(athleteService.getAthletes());
        gameResults.setAll(resultService.getResultsForGame(game.getId()).stream()
                .map(result -> {
                    Athlete athlete = athletes.stream()
                            .filter(a -> a.getId().equals(result.getAthleteId()))
                            .findFirst()
                            .orElse(null);
                    return new AthleteGameResult(result, athlete);
                }).collect(Collectors.toList()));
        athletesResults.setAll(athleteService.getAthletesTotalPoints().entrySet());
    }

    private void startNotificationListener() {
        Thread thread = new Thread(() ->
                SocketManager.runWithSocket(SocketManager.getServerHost(), SocketManager.getNotifierServerPort(),
                        e -> Client.showAlert(Alert.AlertType.ERROR, e.toString(), ButtonType.CLOSE),
                        (socket, outputStream, inputStream) -> {
                            while (inputStream.readObject() == null) {
                                Platform.runLater(this::initializeData);
                            }
                        }
                ));
        thread.setDaemon(true);
        thread.start();
    }

    @FXML
    private void initialize() {
        pane.sceneProperty().addListener((observable, oldValue, newValue) -> {
            if (oldValue != null && oldValue.getRoot() == pane) {
                pointsField.setText("");
            }
            if (newValue != null && newValue.getRoot() == pane) {
                initializeData();
                gameField.setText(game.getName());
                refereeField.setText(authController.getReferee().getName());
            }
        });

        athletePicker.setItems(athletes.sorted(Comparator.comparing(Athlete::getName)));
        athletePicker.setConverter(new StringConverter<Athlete>() {
            @Override
            public String toString(Athlete athlete) {
                return athlete.getName();
            }

            @Override
            public Athlete fromString(String string) {
                return null;
            }
        });

        athletesResultsList.setItems(athletesResults.sorted(Comparator.comparing(Map.Entry::getKey)));

        SortedList<AthleteGameResult> gameResultSortedList = gameResults.sorted();
        gameResultSortedList.comparatorProperty().bind(gameResultsTable.comparatorProperty());
        gameResultsAthleteColumn.setCellValueFactory(new PropertyValueFactory<>("athleteName"));
        gameResultsPointsColumn.setCellValueFactory(new PropertyValueFactory<>("resultPoints"));
        gameResultsTable.getSortOrder().add(gameResultsPointsColumn);
        gameResultsTable.setItems(gameResultSortedList);

        startNotificationListener();
    }

    @FXML
    private void handleExitButtonAction() {
        Client.activatePane(Client.AppPane.AUTH);
        authController.invalidateReferee();
        invalidateData();
    }

    @FXML
    private void handleSubmitButtonAction() {
        Athlete athlete = athletePicker.getSelectionModel().getSelectedItem();
        if (athlete == null) {
            Client.showAlert(Alert.AlertType.ERROR, "No athlete selected!", ButtonType.CLOSE);
            return;
        }

        float points;
        try {
            points = Float.parseFloat(pointsField.getText());
            if (points < 0 || points > 10) {
                throw new NumberFormatException("Outside range 0 - 10");
            }
        } catch (NumberFormatException e) {
            Client.showAlert(Alert.AlertType.ERROR, e.getMessage(), ButtonType.CLOSE);
            return;
        }

        resultService.setResult(athlete.getId(), game.getId(), points);
    }
}
