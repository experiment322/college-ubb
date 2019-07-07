package domain.validator;

import domain.Student;

public class StudentValidator extends BaseEntityValidator {
    @Override
    public void validate(Object entity) throws ValidationException {
        super.validate(entity);
        if (!(entity instanceof Student)) {
            throw new ValidationException("entity not instance of Student");
        }
        Student student = (Student) entity;
        // validate group
        if (student.getGroup() == null
                || student.getGroup() < 0) {
            throw new ValidationException("group is invalid (null or negative)");
        }
        // validate name
        if (student.getName() == null
                || !student.getName().matches("^[A-Z][a-z]+([ -][A-Z][a-z]+)+$")) {
            throw new ValidationException("name is invalid (null or malformed)");
        }
        // validate email
        if (student.getEmail() == null
                || !student.getEmail().matches("^\\w+@\\w+\\.\\w+$")) {
            throw new ValidationException("email is invalid (null or malformed)");
        }
        // validate teacher name
        if (student.getTeacherName() == null
                || !student.getTeacherName().matches("^[A-Z][a-z]+([ -][A-Z][a-z]+)+$")) {
            throw new ValidationException("teacherName is invalid (null or malformed)");
        }
    }
}
