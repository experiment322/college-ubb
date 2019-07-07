package ui.tui;

import service.TaskService;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Stream;

class TaskTUI extends BaseTUI {
    private TaskService taskService;

    TaskTUI(TaskService taskService) {
        this.taskService = taskService;
        generateTUI(
                "Task TUI",
                new HashMap<String, Runnable>() {{
                    put("Create task", TaskTUI.this::createTask);
                    put("Read one task", TaskTUI.this::readOneTask);
                    put("Read all tasks", TaskTUI.this::readAllTasks);
                    put("Update task", TaskTUI.this::updateTask);
                    put("Delete task", TaskTUI.this::deleteTask);
                    put("Extend task deadline", TaskTUI.this::extendTaskDeadline);
                }});
    }

    private void createTask() {
        Map<String, String> taskMap = readMap("id", "assignmentWeek", "deadlineWeek", "description");
        System.console().printf("Operation %s\n", taskService.createTask(taskMap) ? "successful" : "failed");
    }

    private void readOneTask() {
        String taskId = readOne("id");
        Stream.of(taskService.readOneTask(taskId))
                .filter(s -> !s.isEmpty())
                .forEach(s -> System.console().printf("%s\n", s));
    }

    private void readAllTasks() {
        taskService.readAllTasks()
                .forEach(s -> System.console().printf("%s\n", s));
    }

    private void updateTask() {
        Map<String, String> taskMap = readMap("id", "assignmentWeek", "deadlineWeek", "description");
        System.console().printf("Operation %s\n", taskService.updateTask(taskMap) ? "successful" : "failed");
    }

    private void deleteTask() {
        String taskId = readOne("id");
        System.console().printf("Operation %s\n", taskService.deleteTask(taskId) ? "successful" : "failed");
    }

    private void extendTaskDeadline() {
        String taskId = readOne("taskId");
        String newDeadlineWeek = readOne("newDeadlineWeek");
        System.console().printf("Operation %s\n", taskService.extendTaskDeadline(taskId, newDeadlineWeek) ? "successful" : "failed");
    }
}
