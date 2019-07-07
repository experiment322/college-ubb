package ui.tui;

import service.HomeworkService;

import java.util.HashMap;
import java.util.Map;

class HomeworkTUI extends BaseTUI {
    private HomeworkService homeworkService;

    HomeworkTUI(HomeworkService homeworkService) {
        this.homeworkService = homeworkService;
        generateTUI("Homework TUI", new HashMap<String, Runnable>() {{
            put("Create homework", HomeworkTUI.this::createHomework);
            put("Read one homework", HomeworkTUI.this::readOneHomework);
            put("Read all homework", HomeworkTUI.this::readAllHomework);
            put("Update homework", HomeworkTUI.this::updateHomework);
            put("Delete homework", HomeworkTUI.this::deleteHomework);
            put("Extend homework deadline", HomeworkTUI.this::extendHomeworkDeadline);
        }});
    }

    private void createHomework() {
        Map<String, String> homeworkMap = readMap("id", "deadlineWeek", "assignmentWeek", "description");
        System.console().printf("Operation %s\n", homeworkService.createHomework(homeworkMap) ? "successful" : "failed");
    }

    private void readOneHomework() {
        String homeworkId = readOne("id");
        System.console().printf("%s\n", homeworkService.readOneHomework(homeworkId));
    }

    private void readAllHomework() {
        for (String homework : homeworkService.readAllHomework()) {
            System.console().printf("%s\n", homework);
        }
    }

    private void updateHomework() {
        Map<String, String> homeworkMap = readMap("id", "deadlineWeek", "assignmentWeek", "description");
        System.console().printf("Operation %s\n", homeworkService.updateHomework(homeworkMap) ? "successful" : "failed");
    }

    private void deleteHomework() {
        String homeworkId = readOne("id");
        System.console().printf("Operation %s\n", homeworkService.deleteHomework(homeworkId) ? "successful" : "failed");
    }

    private void extendHomeworkDeadline() {
        String homeworkId = readOne("id");
        String newDeadlineWeek = readOne("newDeadlineWeek");
        System.console().printf("Operation %s\n", homeworkService.extendHomeworkDeadline(homeworkId, newDeadlineWeek) ? "successful" : "failed");
    }
}
