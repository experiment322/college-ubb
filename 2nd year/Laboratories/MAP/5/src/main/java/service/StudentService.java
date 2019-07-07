package service;

import domain.Student;
import domain.validator.ValidationException;
import repository.CrudRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class StudentService {
    private CrudRepository<Integer, Student> repository;

    public StudentService(CrudRepository<Integer, Student> repository) {
        this.repository = repository;
    }

    /**
     * Create a new student from the input data
     *
     * @param studentMap key-value pairs corresponding to the student class
     * @return true if saved; false otherwise
     * @throws NumberFormatException thrown when studentMap contains an invalid number for id, group
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean createStudent(Map<String, String> studentMap)
            throws NumberFormatException, ValidationException {
        Student student = new Student(
                Integer.valueOf(studentMap.get("id")),
                Integer.valueOf(studentMap.get("group")),
                studentMap.get("name"),
                studentMap.get("email"),
                studentMap.get("teacherName")
        );
        return repository.save(student) == null;
    }

    /**
     * Read the student with the given id
     *
     * @param id number representing the student id
     * @return found student as string; empty string otherwise
     * @throws NumberFormatException thrown when id string is empty or contains an invalid number
     */
    public String readOneStudent(String id) throws NumberFormatException {
        Student student = repository.findOne(Integer.valueOf(id));
        return student != null ? student.toString() : "";
    }

    /**
     * Read all students
     *
     * @return a string list of all students
     */
    public List<String> readAllStudents() {
        List<String> list = new ArrayList<>();
        for (Student student : repository.findAll()) {
            list.add(student.toString());
        }
        return list;
    }

    /**
     * Update the student from the input data
     *
     * @param studentMap key-value pairs corresponding to the student class
     * @return true if updated; false otherwise
     * @throws NumberFormatException thrown when studentMap contains an invalid number for id, group
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean updateStudent(Map<String, String> studentMap)
            throws NumberFormatException, ValidationException {
        Student student = new Student(
                Integer.valueOf(studentMap.get("id")),
                Integer.valueOf(studentMap.get("group")),
                studentMap.get("name"),
                studentMap.get("email"),
                studentMap.get("teacherName")
        );
        return repository.update(student) == null;
    }

    /**
     * Delete the student with the given id
     *
     * @param id number representing the student id
     * @return true if student is found and deleted; false otherwise
     * @throws NumberFormatException thrown when id string is empty or contains an invalid number
     */
    public Boolean deleteStudent(String id) throws NumberFormatException {
        return repository.delete(Integer.valueOf(id)) != null;
    }
}
