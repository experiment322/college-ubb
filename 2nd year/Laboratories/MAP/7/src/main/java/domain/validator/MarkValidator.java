package domain.validator;

import domain.Mark;

public class MarkValidator implements Validator<Mark> {
    @Override
    public void validate(Mark mark) throws ValidationException {
        // validate id
        String id = mark.getId();
        Integer taskId = mark.getTaskId();
        Integer studentId = mark.getStudentId();
        if (id == null || taskId < 0 || studentId < 0) {
            throw new ValidationException("Id is invalid (null or negative)");
        }

        // validate value
        Double value = mark.getValue();
        if (value == null || value < 1 || value > 10) {
            throw new ValidationException("Value is invalid (null or not between 1-10)");
        }

        // validate week
        Integer week = mark.getWeek();
        if (week == null || week < 1 || week > 28) {
            throw new ValidationException("Week is invalid (null or not between 1-28)");
        }

        // validate feedback
        String feedback = mark.getFeedback();
        if (feedback == null || feedback.length() == 0) {
            throw new ValidationException("Feedback is invalid (null or empty)");
        }
    }
}
