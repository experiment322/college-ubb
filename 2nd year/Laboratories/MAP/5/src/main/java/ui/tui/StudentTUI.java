package ui.tui;

import service.StudentService;

import java.util.HashMap;
import java.util.Map;

public class StudentTUI extends BaseTUI {
    private StudentService studentService;

    public StudentTUI(StudentService studentService) {
        this.studentService = studentService;
        generateTUI("Student TUI", new HashMap<String, Runnable>() {{
            put("Create student", StudentTUI.this::createStudent);
            put("Read one student", StudentTUI.this::readOneStudent);
            put("Read all students", StudentTUI.this::readAllStudents);
            put("Update student", StudentTUI.this::updateStudent);
            put("Delete student", StudentTUI.this::deleteStudent);
        }});
    }

    private void createStudent() {
        Map<String, String> studentMap = readMap("id", "group", "name", "email", "teacherName");
        System.console().printf("Operation %s\n", studentService.createStudent(studentMap) ? "successful" : "failed");
    }

    private void readOneStudent() {
        String studentId = readOne("id");
        System.console().printf("%s\n", studentService.readOneStudent(studentId));
    }

    private void readAllStudents() {
        for (String student : studentService.readAllStudents()) {
            System.console().printf("%s\n", student);
        }
    }

    private void updateStudent() {
        Map<String, String> studentMap = readMap("id", "group", "name", "email", "teacherName");
        System.console().printf("Operation %s\n", studentService.updateStudent(studentMap) ? "successful" : "failed");
    }

    private void deleteStudent() {
        String studentId = readOne("id");
        System.console().printf("Operation %s\n", studentService.deleteStudent(studentId) ? "successful" : "failed");
    }
}
