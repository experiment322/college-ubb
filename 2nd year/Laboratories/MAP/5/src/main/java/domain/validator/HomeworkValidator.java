package domain.validator;

import domain.Homework;

public class HomeworkValidator extends BaseEntityValidator {
    @Override
    public void validate(Object entity) throws ValidationException {
        super.validate(entity);
        if (!(entity instanceof Homework)) {
            throw new ValidationException("entity not instance of Homework");
        }
        Homework homework = (Homework) entity;
        // validate assignment week
        if (homework.getAssignmentWeek() == null
                || homework.getAssignmentWeek() < 1
                || homework.getAssignmentWeek() > 28) {
            throw new ValidationException("assignmentWeek is invalid (null or not between 1-28)");
        }
        // validate deadline week
        if (homework.getDeadlineWeek() == null
                || homework.getDeadlineWeek() < homework.getAssignmentWeek()
                || homework.getDeadlineWeek() > 28) {
            throw new ValidationException("deadlineWeek is invalid (null or not between assignmentWeek-28)");
        }
        // validate description
        if (homework.getDescription() == null
                || homework.getDescription().length() == 0) {
            throw new ValidationException("description is invalid (null or empty)");
        }
    }
}
