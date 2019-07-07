package service;

import domain.Homework;
import domain.validator.ValidationException;
import repository.CrudRepository;

import java.util.Map;

public class HomeworkService {
    private CrudRepository<Integer, Homework> repository;

    HomeworkService(CrudRepository<Integer, Homework> repository) {
        this.repository = repository;
    }

    /**
     * Create a new homework from the input data
     *
     * @param homeworkMap key-value pairs corresponding to the homework class
     * @return true if saved; false otherwise
     * @throws NumberFormatException thrown when homeworkMap contains an invalid number for id, deadlineWeek, assignmentWeek
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean newHomework(Map<String, String> homeworkMap)
            throws NumberFormatException, ValidationException {
        Homework homework = new Homework(
                Integer.valueOf(homeworkMap.get("id")),
                Integer.valueOf(homeworkMap.get("deadlineWeek")),
                Integer.valueOf(homeworkMap.get("assignmentWeek")),
                homeworkMap.get("description")
        );
        return repository.save(homework) == null;
    }

    /**
     * Extend the homework's deadline if it isn't due yet
     *
     * @param homeworkId      id of the homework
     * @param newDeadlineWeek week number
     * @return true if updated; false otherwise
     * @throws NumberFormatException thrown when homeworkId is not a valid number
     * @throws ValidationException   thrown when the new deadline is invalid
     */
    public Boolean extendHomeworkDeadline(String homeworkId, String newDeadlineWeek)
            throws NumberFormatException, ValidationException {
        Homework homework = repository.findOne(Integer.valueOf(homeworkId));
        if (homework != null) {
            Homework updatedHomework = new Homework(homework);
            updatedHomework.setDeadlineWeek(Integer.valueOf(newDeadlineWeek));
            return repository.update(updatedHomework) == null;
        }
        return false;
    }
}
