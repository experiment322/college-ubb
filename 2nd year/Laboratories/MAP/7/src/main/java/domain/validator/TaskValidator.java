package domain.validator;

import domain.Task;

public class TaskValidator implements Validator<Task> {
    @Override
    public void validate(Task task) throws ValidationException {
        // validate id
        Integer id = task.getId();
        if (id == null || id < 0) {
            throw new ValidationException("Id is invalid (null or negative)");
        }

        // validate assignment week
        Integer assignmentWeek = task.getAssignmentWeek();
        if (assignmentWeek == null || assignmentWeek < 1 || assignmentWeek > 28) {
            throw new ValidationException("AssignmentWeek is invalid (null or not between 1-28)");
        }

        // validate deadline week
        Integer deadlineWeek = task.getDeadlineWeek();
        if (deadlineWeek == null || deadlineWeek <= task.getAssignmentWeek() || deadlineWeek > 28) {
            throw new ValidationException("DeadlineWeek is invalid (null or not between (AssignmentWeek+1)-28)");
        }

        // validate description
        String description = task.getDescription();
        if (description == null || description.length() == 0) {
            throw new ValidationException("Description is invalid (null or empty)");
        }
    }
}
