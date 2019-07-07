package ui.tui;

import service.MarkService;

import java.util.HashMap;
import java.util.Map;

class MarkTUI extends BaseTUI {
    private MarkService markService;

    MarkTUI(MarkService markService) {
        this.markService = markService;
        generateTUI(
                "Mark TUI",
                new HashMap<String, Runnable>() {{
                    put("Add mark", MarkTUI.this::addMark);
                }}
        );
    }

    private void addMark() {
        Map<String, String> markMap = readMap("taskId", "studentId", "value", "feedback");
        Boolean didCreateMark = markService.createMark(markMap);
        if (didCreateMark) {
            Double maximumMarkValue = markService.getMaximumMarkValue(markMap);
            if (Double.valueOf(markMap.get("value")) > maximumMarkValue) {
                System.console().printf("Mark value was set to %.2f because the task was due\n", maximumMarkValue);
            }
            System.console().printf("Saving mark to student's file %s\n",
                    markService.dumpMarkToStudentFile(markMap) ? "successful" : "failed");
        }
        System.console().printf("Operation %s\n", didCreateMark ? "successful" : "failed");
    }
}
