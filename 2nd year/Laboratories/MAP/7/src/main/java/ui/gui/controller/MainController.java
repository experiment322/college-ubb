package ui.gui.controller;

import domain.Mark;
import domain.Student;
import domain.Task;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Region;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import ui.gui.MainGUI;
import utils.EntityUtils;
import utils.NumberUtils;
import utils.WeekUtils;

import java.time.LocalDate;
import java.time.ZoneId;
import java.util.*;
import java.util.stream.Collectors;

public class MainController {
    @FXML
    private TabPane tabPane;
    @FXML
    private Tab tabMarks;
    @FXML
    private Tab tabTasks;
    @FXML
    private Tab tabStudents;

    @FXML
    private void initialize() {
        initializeStudents();
        initializeMarks();
    }

    @FXML
    private void fileMarksAction() {
        tabPane.getSelectionModel().select(tabMarks);
    }

    @FXML
    private void fileTasksAction() {
        tabPane.getSelectionModel().select(tabTasks);
    }

    @FXML
    private void fileStudentsAction() {
        tabPane.getSelectionModel().select(tabStudents);
    }

    @FXML
    private void fileCloseAction() {
        Stage stage = (Stage) tabPane.getScene().getWindow();
        stage.close();
    }

    private void showAlert(Alert.AlertType alertType, String message) {
        Alert alert = new Alert(alertType, message, ButtonType.OK);
        alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
        alert.show();
    }

    // mark stuff
    @FXML
    private ComboBox<Task> markTaskComboBox;
    @FXML
    private ComboBox<Student> markStudentComboBox;
    @FXML
    private ComboBox<Integer> markStudentGroupComboBox;
    @FXML
    private DatePicker markStartDatePicker;
    @FXML
    private DatePicker markEndDatePicker;
    @FXML
    private TextField markValueTextField;
    @FXML
    private TextArea markFeedbackTextArea;
    @FXML
    private TableView<Mark> markTableView;

    private ObservableList<Mark> marks;
    private FilteredList<Mark> markFilteredList;

    private HashMap<String, String> getMarkMap() {
        return new HashMap<String, String>() {{
            put("taskId",
                    Optional.of(markTaskComboBox.getSelectionModel().getSelectedItem())
                            .map(task -> task.getId().toString())
                            .orElse(null)
            );
            put("studentId",
                    Optional.of(markStudentComboBox.getSelectionModel().getSelectedItem())
                            .map(student -> student.getId().toString())
                            .orElse(null)
            );
            put("value", markValueTextField.getText());
            put("feedback", markFeedbackTextArea.getText());
        }};
    }

    private void selectCurrentTask() {
        Integer currentWeek = MainGUI.getTaskService().getWeekUtils().getCurrentDidacticWeek();
        if (currentWeek != 0) {
            Task currentTask = MainGUI.getTaskService().readAllTasks().stream()
                    .map(s -> EntityUtils.fromString(new Task(), s))
                    .filter(Objects::nonNull)
                    .sorted(Comparator.comparingInt(Task::getDeadlineWeek).reversed())
                    .filter(task -> task.getDeadlineWeek() <= currentWeek)
                    .findFirst()
                    .orElse(null);
            markTaskComboBox.getSelectionModel().select(currentTask);
        }
    }

    private void initializeMarkTasks() {
        ObservableList<Task> markTasks = FXCollections.observableArrayList(
                MainGUI.getTaskService().readAllTasks().stream()
                        .map(s -> EntityUtils.fromString(new Task(), s))
                        .collect(Collectors.toList())
        );
        markTaskComboBox.setConverter(new StringConverter<Task>() {
            @Override
            public String toString(Task object) {
                return object.getDescription();
            }

            @Override
            public Task fromString(String string) {
                return null;
            }
        });
        markTaskComboBox.setItems(markTasks);
        selectCurrentTask();
    }

    private void initializeMarkStudents() {
        FilteredList<Student> studentFilteredList = new FilteredList<>(students, student -> true);
        markStudentComboBox.setConverter(new StringConverter<Student>() {
            @Override
            public String toString(Student object) {
                if (object != null) {
                    return object.getId().toString() + " " + object.getName();
                }
                return null;
            }

            @Override
            public Student fromString(String string) {
                return studentFilteredList.stream()
                        .filter(student -> string.equals(student.getId().toString() + " " + student.getName()))
                        .findFirst()
                        .orElse(null);
            }
        });
        markStudentComboBox.getEditor().textProperty().addListener((observable, oldValue, newValue) -> {
            Student selectedStudent = markStudentComboBox.getSelectionModel().getSelectedItem();
            Platform.runLater(() -> {
                if (selectedStudent == null || !newValue.equals(markStudentComboBox.getConverter().toString(selectedStudent))) {
                    studentFilteredList.setPredicate(student ->
                            student.getName().toLowerCase().contains(newValue.toLowerCase())
                    );
                    markStudentComboBox.getEditor().positionCaret(markStudentComboBox.getEditor().getText().length());
                }
            });
            if (newValue.isEmpty()) {
                markStudentComboBox.hide();
            } else if (!markStudentComboBox.isShowing()) {
                markStudentComboBox.show();
            }
        });
        markStudentComboBox.setItems(studentFilteredList);
    }

    private void initializeMarkStudentGroups() {
        ObservableList<Integer> markStudentGroups = students.stream()
                .mapToInt(Student::getGroup)
                .distinct()
                .boxed()
                .collect(Collectors.toCollection(FXCollections::observableArrayList));
        students.addListener((ListChangeListener<Student>) c ->
                markStudentGroups.setAll(students.stream()
                        .mapToInt(Student::getGroup)
                        .distinct()
                        .boxed()
                        .collect(Collectors.toList())));
        markStudentGroupComboBox.setItems(markStudentGroups);
    }

    private void initializeMarkValueTextField() {
        markValueTextField.textProperty().addListener((observable, oldValue, newValue) ->
                Platform.runLater(() -> {
                    try {
                        if (newValue.isEmpty()) return;
                        Double value = Double.valueOf(newValue);
                        if (value < 1.0 || value > 10.0) {
                            throw new ArithmeticException();
                        }
                        if (newValue.length() > 6) {
                            markValueTextField.setText(newValue.substring(0, 6));
                        }
                    } catch (Exception e) {
                        markValueTextField.setText(oldValue);
                    } finally {
                        markValueTextField.positionCaret(markValueTextField.getText().length());
                    }
                }));
    }

    private void initializeMarkFeedbackTextArea() {
        ChangeListener<Object> changeListener = (observable, oldValue, newValue) ->
                Platform.runLater(() -> {
                    Task task = markTaskComboBox.getSelectionModel().getSelectedItem();
                    Student student = markStudentComboBox.getSelectionModel().getSelectedItem();
                    Double value = NumberUtils.tryParseDouble(markValueTextField.getText());
                    if (task != null && student != null && value != null) {
                        Double maxValue = MainGUI.getMarkService().getMaximumMarkValue(new HashMap<String, String>() {{
                            put("taskId", task.getId().toString());
                            put("studentId", student.getId().toString());
                        }});
                        if (maxValue != null && value > maxValue) {
                            markFeedbackTextArea.setText(
                                    "NOTA A FOST DIMINUATA CU " +
                                            String.format("%.2f", (value - maxValue)) + " PUNCTE DATORITA INTARZIERILOR"
                            );
                        } else {
                            markFeedbackTextArea.setText("");
                        }
                    }
                });
        markValueTextField.textProperty().addListener(changeListener);
        markTaskComboBox.getSelectionModel().selectedItemProperty().addListener(changeListener);
        markStudentComboBox.getSelectionModel().selectedItemProperty().addListener(changeListener);
    }

    @FXML
    private void initializeMarks() {
        initializeMarkTasks();
        initializeMarkStudents();
        initializeMarkStudentGroups();
        initializeMarkValueTextField();
        initializeMarkFeedbackTextArea();
        markTableView.getColumns().forEach(markTableColumn -> markTableColumn.setCellValueFactory(
                new PropertyValueFactory<>(markTableColumn.getText())
        ));
        marks = FXCollections.observableArrayList(
                MainGUI.getMarkService().readAllMarks().stream()
                        .map(s -> EntityUtils.fromString(new Mark(), s))
                        .collect(Collectors.toList())
        );
        markFilteredList = new FilteredList<>(marks, mark -> true);
        markTableView.setItems(markFilteredList);
        MainGUI.getMarkService().watchRepositoryChanges(change -> marks.setAll(change.getMap().values()));
    }

    @FXML
    private void markStudentComboBoxOnAction() {
        markStudentComboBox.getEditor().positionCaret(markStudentComboBox.getEditor().getText().length());
    }

    @FXML
    private void markConfirmOnAction() {
        Task task = markTaskComboBox.getSelectionModel().getSelectedItem();
        Student student = markStudentComboBox.getSelectionModel().getSelectedItem();
        Double value = NumberUtils.tryParseDouble(markValueTextField.getText());
        if (task != null && student != null && value != null) {
            Double maxValue = MainGUI.getMarkService().getMaximumMarkValue(new HashMap<String, String>() {{
                put("taskId", task.getId().toString());
                put("studentId", student.getId().toString());
            }});
            if (maxValue == null) {
                showAlert(Alert.AlertType.ERROR,
                        "Cannot give a mark anymore to the selected student. " +
                                "Do not forget to justify its absences if appropriate");
                return;
            }
            String markSummary = "Tema: " + task.getDescription() + "\n" +
                    "Student: " + student.getName() + "\n" +
                    "Nota: " + value + "\n" +
                    "Penalizare: " + Math.min(maxValue - value, 0) + "\n";
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION, markSummary, ButtonType.APPLY, ButtonType.CANCEL);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            Optional<ButtonType> response = alert.showAndWait();
            response.ifPresent(buttonType -> {
                if (buttonType == ButtonType.APPLY) {
                    if (MainGUI.getMarkService().createMark(getMarkMap())) {
                        showAlert(Alert.AlertType.INFORMATION,
                                "Mark given successfully");
                    } else {
                        showAlert(Alert.AlertType.WARNING,
                                "There is already a mark given for the task-student combination");
                    }
                }
            });
        } else {
            showAlert(Alert.AlertType.ERROR,
                    "Please fill all the required fileds to proceed");
        }
    }

    @FXML
    private void resetMarksFilterOnAction() {
        markFilteredList.setPredicate(mark -> true);
    }

    @FXML
    private void filterMarksByTaskOnAction() {
        Task selectedTask = markTaskComboBox.getSelectionModel().getSelectedItem();
        if (selectedTask != null) {
            markFilteredList.setPredicate(mark -> mark.getTaskId().equals(selectedTask.getId()));
        } else {
            showAlert(Alert.AlertType.ERROR, "Please select a task first");
        }
    }

    @FXML
    private void filterMarksByStudentOnAction() {
        Student selectedStudent = markStudentComboBox.getSelectionModel().getSelectedItem();
        if (selectedStudent != null) {
            markFilteredList.setPredicate(mark -> mark.getStudentId().equals(selectedStudent.getId()));
        } else {
            showAlert(Alert.AlertType.ERROR, "Please select a student first");
        }
    }

    @FXML
    private void filterMarksByTaskAndStudentGroupOnAction() {
        Task selectedTask = markTaskComboBox.getSelectionModel().getSelectedItem();
        Integer selectedStudentGroup = markStudentGroupComboBox.getSelectionModel().getSelectedItem();
        if (selectedTask != null && selectedStudentGroup != null) {
            markFilteredList.setPredicate(mark -> {
                Student student = students.stream()
                        .filter(s -> s.getId().equals(mark.getStudentId()))
                        .findFirst()
                        .orElse(null);
                return student != null &&
                        student.getGroup().equals(selectedStudentGroup) &&
                        mark.getTaskId().equals(selectedTask.getId());
            });
        } else {
            if (selectedTask == null) {
                showAlert(Alert.AlertType.ERROR, "Please select a task first");
            }
            if (selectedStudentGroup == null) {
                showAlert(Alert.AlertType.ERROR, "Please select a student group first");
            }
        }
    }

    @FXML
    private void filterMarksByPeriodOnAction() {
        LocalDate startDate = markStartDatePicker.getValue();
        LocalDate endDate = markEndDatePicker.getValue();
        if (startDate != null && endDate != null) {
            Calendar startCalendar = Calendar.getInstance();
            startCalendar.setTime(Date.from(startDate.atStartOfDay(ZoneId.systemDefault()).toInstant()));
            startCalendar.add(Calendar.DATE, -1);
            Calendar endCalendar = Calendar.getInstance();
            endCalendar.setTime(Date.from(endDate.atStartOfDay(ZoneId.systemDefault()).toInstant()));
            endCalendar.add(Calendar.DATE, +1);
            WeekUtils weekUtils = MainGUI.getMarkService().getWeekUtils();
            markFilteredList.setPredicate(mark -> {
                Calendar markCalendar = weekUtils.getCalendarForDidacticWeek(mark.getWeek());
                return markCalendar.after(startCalendar) && markCalendar.before(endCalendar);
            });
        } else {
            if (startDate == null) {
                showAlert(Alert.AlertType.ERROR, "Please select a starting date first");
            }
            if (endDate == null) {
                showAlert(Alert.AlertType.ERROR, "Please select an ending date first");
            }
        }
    }
    // end of mark stuff

    // student stuff
    @FXML
    private TextField studentIdField;
    @FXML
    private TextField studentGroupField;
    @FXML
    private TextField studentNameField;
    @FXML
    private TextField studentEmailField;
    @FXML
    private TextField studentTeacherNameField;
    @FXML
    private VBox absencesBox;
    @FXML
    private ScrollPane absencesScrollPane;
    @FXML
    private VBox justifiedAbsencesBox;
    @FXML
    private ScrollPane justifiedAbsencesScrollPane;
    @FXML
    private TableView<Student> studentTableView;

    private ObservableList<Student> students;

    private void fillStudentFields(Student student) {
        studentIdField.setText(student.getId().toString());
        studentGroupField.setText(student.getGroup().toString());
        studentNameField.setText(student.getName());
        studentEmailField.setText(student.getEmail());
        studentTeacherNameField.setText(student.getTeacherName());
        absencesBox.getChildren().forEach(node -> {
            CheckBox checkBox = (CheckBox) node;
            checkBox.setSelected(student.getAbsences().testBit(Integer.valueOf(checkBox.getText()) - 1));
        });
        justifiedAbsencesBox.getChildren().forEach(node -> {
            CheckBox checkBox = (CheckBox) node;
            checkBox.setSelected(student.getJustifiedAbsences().testBit(Integer.valueOf(checkBox.getText()) - 1));
        });
    }

    private void clearStudentFields() {
        studentIdField.setText("");
        studentGroupField.setText("");
        studentNameField.setText("");
        studentEmailField.setText("");
        studentTeacherNameField.setText("");
        absencesBox.getChildren().forEach(node -> {
            CheckBox checkBox = (CheckBox) node;
            checkBox.setSelected(false);
        });
        justifiedAbsencesBox.getChildren().forEach(node -> {
            CheckBox checkBox = (CheckBox) node;
            checkBox.setSelected(false);
        });
    }

    private void initializeStudents() {
        // setup and fill table view with initial data
        students = FXCollections.observableArrayList(
                MainGUI.getStudentService().readAllStudents().stream()
                        .map(s -> EntityUtils.fromString(new Student(), s))
                        .collect(Collectors.toList())
        );
        studentTableView.getColumns().forEach(studentTableColumn -> studentTableColumn.setCellValueFactory(
                new PropertyValueFactory<>(studentTableColumn.getText())
        ));
        studentTableView.setItems(students);
        // fill fields with selected item
        studentTableView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                fillStudentFields(newValue);
            } else {
                clearStudentFields();
            }
        });
        // update gui students after a change in repository; also keep table view selection
        MainGUI.getStudentService().watchRepositoryChanges(change -> {
            String studentId = null;
            Student selectedStudent = studentTableView.getSelectionModel().getSelectedItem();
            if (selectedStudent != null) {
                studentId = selectedStudent.getId().toString();
            }
            students.setAll(change.getMap().values());
            studentTableView.sort();
            if (studentId == null) {
                studentTableView.getSelectionModel().select(null);
            } else {
                String student = MainGUI.getStudentService().readOneStudent(studentId);
                studentTableView.getSelectionModel().select(EntityUtils.fromString(new Student(), student));
            }
        });
        // sync absences scroll panes
        absencesScrollPane.vvalueProperty().addListener((observable, oldValue, newValue) ->
                justifiedAbsencesScrollPane.setVvalue(newValue.doubleValue())
        );
        justifiedAbsencesScrollPane.vvalueProperty().addListener((observable, oldValue, newValue) ->
                absencesScrollPane.setVvalue(newValue.doubleValue())
        );
    }

    private HashMap<String, String> getStudentMap() {
        return new HashMap<String, String>() {{
            put("id", studentIdField.getText());
            put("group", studentGroupField.getText());
            put("name", studentNameField.getText());
            put("email", studentEmailField.getText());
            put("teacherName", studentTeacherNameField.getText());
        }};
    }

    @FXML
    private void newStudentAction() {
        try {
            Boolean wasCreated = MainGUI.getStudentService().createStudent(getStudentMap());
            if (!wasCreated) {
                throw new Exception("Student already exists");
            }
        } catch (Exception e) {
            showAlert(Alert.AlertType.ERROR, e.getMessage());
        }
    }

    @FXML
    private void updateStudentAction() {
        try {
            Boolean wasUpdated = MainGUI.getStudentService().updateStudent(getStudentMap());
            if (!wasUpdated) {
                throw new Exception("Student does not exist");
            }
        } catch (Exception e) {
            showAlert(Alert.AlertType.ERROR, e.getMessage());
        }
    }

    @FXML
    private void deleteStudentAction() {
        Student student = studentTableView.getSelectionModel().getSelectedItem();
        if (student != null) {
            MainGUI.getStudentService().deleteStudent(student.getId().toString());
        } else {
            showAlert(Alert.AlertType.INFORMATION, "Please select a student first");
        }
    }

    @FXML
    private void studentFieldAction() {
        String result;
        try {
            result = MainGUI.getStudentService().readOneStudent(getStudentMap().get("id"));
        } catch (Exception e) {
            result = "";
        }
        if (result.equals("")) {
            newStudentAction();
        } else {
            updateStudentAction();
        }
    }

    @FXML
    private void escPressedAction(KeyEvent event) {
        if (event.getCode().equals(KeyCode.ESCAPE)) {
            studentTableView.getSelectionModel().select(null);
        }
    }

    @FXML
    private void setAbsentAction(ActionEvent event) {
        Student student = studentTableView.getSelectionModel().getSelectedItem();
        CheckBox checkBox = (CheckBox) event.getTarget();
        if (checkBox.isSelected()) {
            if (student == null) {
                showAlert(Alert.AlertType.ERROR, "Please select a student first");
                checkBox.setSelected(false);
            } else {
                checkBox.setSelected(
                        MainGUI.getStudentService()
                                .markStudentAbsent(student.getId().toString(), checkBox.getText())
                );
            }
        } else {
            checkBox.setSelected(true);
        }
    }

    @FXML
    private void justifyAbsenceAction(ActionEvent event) {
        Student student = studentTableView.getSelectionModel().getSelectedItem();
        CheckBox checkBox = (CheckBox) event.getTarget();
        if (checkBox.isSelected()) {
            if (student == null) {
                showAlert(Alert.AlertType.ERROR, "Please select a student first");
                checkBox.setSelected(false);
            } else {
                try {
                    checkBox.setSelected(
                            MainGUI.getStudentService()
                                    .justifyStudentAbsence(student.getId().toString(), checkBox.getText())
                    );
                } catch (Exception e) {
                    checkBox.setSelected(false);
                }
            }
        } else {
            checkBox.setSelected(true);
        }
    }
    // end of student stuff
}
