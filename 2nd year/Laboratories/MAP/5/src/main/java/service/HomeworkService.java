package service;

import domain.Homework;
import domain.validator.ValidationException;
import repository.CrudRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class HomeworkService {
    private CrudRepository<Integer, Homework> repository;

    public HomeworkService(CrudRepository<Integer, Homework> repository) {
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
    public Boolean createHomework(Map<String, String> homeworkMap)
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
     * Read the homework with the given id
     *
     * @param id number representing the homework id
     * @return found homework as string; empty string otherwise
     * @throws NumberFormatException thrown when id string is empty or contains an invalid number
     */
    public String readOneHomework(String id) throws NumberFormatException {
        Homework homework = repository.findOne(Integer.valueOf(id));
        return homework != null ? homework.toString() : "";
    }

    /**
     * Read all homework
     *
     * @return a string list of all homework
     */
    public List<String> readAllHomework() {
        List<String> list = new ArrayList<>();
        for (Homework homework : repository.findAll()) {
            list.add(homework.toString());
        }
        return list;
    }

    /**
     * Update the homework from the input data
     *
     * @param homeworkMap key-value pairs corresponding to the homework class
     * @return true if updated; false otherwise
     * @throws NumberFormatException thrown when homeworkMap contains an invalid number for id, deadlineWeek, assignmentWeek
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean updateHomework(Map<String, String> homeworkMap)
            throws NumberFormatException, ValidationException {
        Homework homework = new Homework(
                Integer.valueOf(homeworkMap.get("id")),
                Integer.valueOf(homeworkMap.get("deadlineWeek")),
                Integer.valueOf(homeworkMap.get("assignmentWeek")),
                homeworkMap.get("description")
        );
        return repository.update(homework) == null;
    }

    /**
     * Delete the homework with the given id
     *
     * @param id number representing the homework id
     * @return true if homework is found and deleted; false otherwise
     * @throws NumberFormatException thrown when id string is empty or contains an invalid number
     */
    public Boolean deleteHomework(String id) throws NumberFormatException {
        return repository.delete(Integer.valueOf(id)) != null;
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
