package service;

import domain.Homework;
import domain.validator.HomeworkValidator;
import domain.validator.ValidationException;
import org.junit.Before;
import org.junit.Test;
import repository.CrudRepository;
import repository.InMemoryRepository;

import java.util.HashMap;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class HomeworkServiceTest {
    private HomeworkService homeworkService;

    @Before
    public void setUp() {
        HomeworkValidator homeworkValidator = new HomeworkValidator();
        CrudRepository<Integer, Homework> homeworkInMemoryRepository = new InMemoryRepository<>(homeworkValidator);
        homeworkService = new HomeworkService(homeworkInMemoryRepository);
        homeworkService.createHomework(new HashMap<String, String>() {{
            put("id", "0");
            put("deadlineWeek", "2");
            put("assignmentWeek", "1");
            put("description", "test description");
        }});
    }

    @Test(expected = NumberFormatException.class)
    public void extendHomeworkDeadlineFail() {
        homeworkService.extendHomeworkDeadline("0q", "3");
    }

    @Test(expected = ValidationException.class)
    public void extendHomeworkDeadlineValidate() {
        homeworkService.extendHomeworkDeadline("0", "0");
    }

    @Test
    public void extendHomeworkDeadline() {
        assertTrue(homeworkService.extendHomeworkDeadline("0", "7"));
        assertFalse(homeworkService.extendHomeworkDeadline("1", "7"));
    }
}
