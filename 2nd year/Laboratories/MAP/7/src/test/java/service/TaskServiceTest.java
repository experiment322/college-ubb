package service;

import domain.Task;
import domain.validator.TaskValidator;
import domain.validator.ValidationException;
import org.junit.Before;
import org.junit.Test;
import repository.CrudRepository;
import repository.InMemoryRepository;

import java.util.HashMap;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class TaskServiceTest {
    private TaskService taskService;

    @Before
    public void setUp() {
        TaskValidator taskValidator = new TaskValidator();
        CrudRepository<Integer, Task> homeworkInMemoryRepository = new InMemoryRepository<>(taskValidator);
        taskService = new TaskService(null, homeworkInMemoryRepository);
        taskService.createTask(new HashMap<String, String>() {{
            put("id", "0");
            put("assignmentWeek", "1");
            put("deadlineWeek", "2");
            put("description", "test description");
        }});
    }

    @Test(expected = NumberFormatException.class)
    public void extendHomeworkDeadlineFail() {
        taskService.extendTaskDeadline("0q", "3");
    }

    @Test(expected = ValidationException.class)
    public void extendHomeworkDeadlineValidate() {
        taskService.extendTaskDeadline("0", "0");
    }

    @Test
    public void extendHomeworkDeadline() {
        assertTrue(taskService.extendTaskDeadline("0", "7"));
        assertFalse(taskService.extendTaskDeadline("1", "7"));
    }
}
