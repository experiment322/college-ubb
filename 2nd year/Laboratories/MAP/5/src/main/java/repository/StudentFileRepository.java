package repository;

import domain.Student;
import domain.validator.Validator;

import java.util.List;

public class StudentFileRepository extends AbstractFileRepository<Integer, Student> {
    public StudentFileRepository(Validator validator) {
        super("students.txt", validator);
    }

    @Override
    Student extractEntity(List<String> attributes) {
        String id = attributes.stream().filter(s -> s.startsWith("id=")).findFirst().get().split("=")[1];
        String group = attributes.stream().filter(s -> s.startsWith("group=")).findFirst().get().split("=")[1];
        String name = attributes.stream().filter(s -> s.startsWith("name=")).findFirst().get().split("=")[1];
        String email = attributes.stream().filter(s -> s.startsWith("email=")).findFirst().get().split("=")[1];
        String teacherName = attributes.stream().filter(s -> s.startsWith("teacherName=")).findFirst().get().split("=")[1];
        return new Student(Integer.valueOf(id), Integer.valueOf(group), name, email, teacherName);
    }
}
