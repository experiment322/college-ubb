package ui.tui;

import service.MarkService;
import service.StudentService;
import service.TaskService;

import java.util.HashMap;

public class MainTUI extends BaseTUI {
    private MarkTUI markTUI;
    private TaskTUI taskTUI;
    private StudentTUI studentTUI;

    public MainTUI(MarkService markService, TaskService taskService, StudentService studentService) {
        this.markTUI = new MarkTUI(markService);
        this.taskTUI = new TaskTUI(taskService);
        this.studentTUI = new StudentTUI(studentService);
        generateTUI(
                "Main TUI",
                new HashMap<String, Runnable>() {{
                    put("Mark menu", MainTUI.this.markTUI::run);
                    put("Task menu", MainTUI.this.taskTUI::run);
                    put("Student menu", MainTUI.this.studentTUI::run);
                }});
    }
}
