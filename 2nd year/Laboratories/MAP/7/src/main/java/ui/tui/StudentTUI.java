package ui.tui;

import service.StudentService;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Stream;

class StudentTUI extends BaseTUI {
    private StudentService studentService;

    StudentTUI(StudentService studentService) {
        this.studentService = studentService;
        generateTUI(
                "Student TUI",
                new HashMap<String, Runnable>() {{
                    put("Create student", StudentTUI.this::createStudent);
                    put("Read one student", StudentTUI.this::readOneStudent);
                    put("Read all students", StudentTUI.this::readAllStudents);
                    put("Update student", StudentTUI.this::updateStudent);
                    put("Delete student", StudentTUI.this::deleteStudent);
                    put("Mark student absent", StudentTUI.this::markStudentAbsent);
                    put("Justify student absence", StudentTUI.this::justifyStudentAbsence);
                }});
    }

    private void createStudent() {
        Map<String, String> studentMap = readMap("id", "group", "name", "email", "teacherName");
        System.console().printf("Operation %s\n", studentService.createStudent(studentMap) ? "successful" : "failed");
    }

    private void readOneStudent() {
        String studentId = readOne("id");
        Stream.of(studentService.readOneStudent(studentId))
                .filter(s -> !s.isEmpty())
                .forEach(s -> System.console().printf("%s\n", s));
    }

    private void readAllStudents() {
        studentService.readAllStudents()
                .forEach(s -> System.console().printf("%s\n", s));
    }

    private void updateStudent() {
        Map<String, String> studentMap = readMap("id", "group", "name", "email", "teacherName");
        System.console().printf("Operation %s\n", studentService.updateStudent(studentMap) ? "successful" : "failed");
    }

    private void deleteStudent() {
        String studentId = readOne("id");
        System.console().printf("Operation %s\n", studentService.deleteStudent(studentId) ? "successful" : "failed");
    }

    private void markStudentAbsent() {
        String studentId = readOne("studentId");
        String absenceWeek = readOne("absenceWeek");
        System.console().printf("Operation %s\n", studentService.markStudentAbsent(studentId, absenceWeek) ? "successful" : "failed");
    }

    private void justifyStudentAbsence() {
        String studentId = readOne("studentId");
        String absenceWeek = readOne("absenceWeek");
        System.console().printf("Operation %s\n", studentService.justifyStudentAbsence(studentId, absenceWeek) ? "successful" : "failed");
    }
}
