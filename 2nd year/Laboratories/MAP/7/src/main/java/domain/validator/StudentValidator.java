package domain.validator;

import domain.Student;

import java.math.BigInteger;

public class StudentValidator implements Validator<Student> {
    @Override
    public void validate(Student student) throws ValidationException {
        // validate id
        Integer id = student.getId();
        if (id == null || id < 0) {
            throw new ValidationException("Id is invalid (null or negative)");
        }

        // validate group
        Integer group = student.getGroup();
        if (group == null || group < 0) {
            throw new ValidationException("Group is invalid (null or negative)");
        }

        // validate name
        String name = student.getName();
        if (name == null || !name.matches("^[A-Z][a-z]+([ -][A-Z][a-z]+)+$")) {
            throw new ValidationException("Name is invalid (null or malformed)");
        }

        // validate email
        String email = student.getEmail();
        if (email == null || !email.matches("^\\w+@\\w+\\.\\w+$")) {
            throw new ValidationException("Email is invalid (null or malformed)");
        }

        // validate teacher name
        String teacherName = student.getTeacherName();
        if (teacherName == null || !teacherName.matches("^[A-Z][a-z]+([ -][A-Z][a-z]+)+$")) {
            throw new ValidationException("TeacherName is invalid (null or malformed)");
        }

        // validate absences
        BigInteger absences = student.getAbsences();
        if (absences == null || absences.signum() < 0 || absences.bitLength() > 28) {
            throw new ValidationException("Absences are invalid (null, negative or more than 28)");
        }

        // validate justifiedAbsences
        BigInteger justifiedAbsences = student.getJustifiedAbsences();
        if (justifiedAbsences == null || justifiedAbsences.signum() < 0 || justifiedAbsences.or(absences).compareTo(absences) != 0) {
            throw new ValidationException("JustifiedAbsences are invalid (null, negative or mismatched with Absences)");
        }
    }
}
