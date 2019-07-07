package ui.tui;

import service.HomeworkService;
import service.StudentService;

import java.util.HashMap;

public class MainTUI extends BaseTUI {
    private StudentTUI studentTUI;
    private HomeworkTUI homeworkTUI;

    public MainTUI(StudentService studentService, HomeworkService homeworkService) {
        this.studentTUI = new StudentTUI(studentService);
        this.homeworkTUI = new HomeworkTUI(homeworkService);
        generateTUI("Main TUI", new HashMap<String, Runnable>() {{
            put("Student menu", MainTUI.this::openStudentTUI);
            put("Homework menu", MainTUI.this::openHomeworkTUI);
        }});
    }

    private void openStudentTUI() {
        studentTUI.run();
    }

    private void openHomeworkTUI() {
        homeworkTUI.run();
    }
}
