package repository;

import domain.Homework;
import domain.validator.Validator;

import java.util.List;

public class HomeworkFileRepository extends AbstractFileRepository<Integer, Homework> {
    public HomeworkFileRepository(Validator validator) {
        super("homework.txt", validator);
    }

    @Override
    Homework extractEntity(List<String> attributes) {
        String id = attributes.stream().filter(s -> s.startsWith("id=")).findFirst().get().split("=")[1];
        String deadlineWeek = attributes.stream().filter(s -> s.startsWith("deadlineWeek=")).findFirst().get().split("=")[1];
        String assignmentWeek = attributes.stream().filter(s -> s.startsWith("assignmentWeek=")).findFirst().get().split("=")[1];
        String description = attributes.stream().filter(s -> s.startsWith("description=")).findFirst().get().split("=")[1];
        return new Homework(Integer.valueOf(id), Integer.valueOf(deadlineWeek), Integer.valueOf(assignmentWeek), description);
    }
}
