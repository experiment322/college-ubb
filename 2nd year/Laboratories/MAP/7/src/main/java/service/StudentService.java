package service;

import domain.Student;
import domain.validator.ValidationException;
import javafx.collections.MapChangeListener;
import repository.CrudRepository;
import utils.EntityUtils;
import utils.NumberUtils;
import utils.WeekUtils;

import java.math.BigInteger;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class StudentService {
    private WeekUtils weekUtils;
    private CrudRepository<Integer, Student> repository;

    public StudentService(WeekUtils weekUtils, CrudRepository<Integer, Student> repository) {
        this.weekUtils = weekUtils;
        this.repository = repository;
    }

    private void fillDefaults(Map<String, String> studentMap) {
        if (!studentMap.containsKey("absences") || studentMap.get("absences").isEmpty()) {
            studentMap.put("absences", "0");
        }
        if (!studentMap.containsKey("justifiedAbsences") || studentMap.get("justifiedAbsences").isEmpty()) {
            studentMap.put("justifiedAbsences", "0");
        }
    }

    private Student fromMap(Map<String, String> studentMap) {
        fillDefaults(studentMap);
        Student student = new Student();
        student.setId(NumberUtils.tryParseInteger(studentMap.get("id")));
        student.setGroup(NumberUtils.tryParseInteger(studentMap.get("group")));
        student.setName(studentMap.get("name"));
        student.setEmail(studentMap.get("email"));
        student.setTeacherName(studentMap.get("teacherName"));
        student.setAbsences(NumberUtils.tryParseBigInteger(studentMap.get("absences")));
        student.setJustifiedAbsences(NumberUtils.tryParseBigInteger(studentMap.get("justifiedAbsences")));
        return student;
    }

    public void watchRepositoryChanges(MapChangeListener<Integer, Student> handler) {
        repository.observeChanges(handler);
    }

    public WeekUtils getWeekUtils() {
        return weekUtils;
    }

    /**
     * Create a new student from the input data
     *
     * @param studentMap key-value pairs corresponding to the student class
     * @return true if saved; false otherwise
     * @throws NumberFormatException thrown when studentMap contains an invalid number for id, group
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean createStudent(Map<String, String> studentMap) throws NumberFormatException, ValidationException {
        Student student = fromMap(studentMap);
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
        return student != null ? EntityUtils.dumpString(student) : "";
    }

    /**
     * Read all students
     *
     * @return a string list of all students
     */
    public List<String> readAllStudents() {
        return StreamSupport.stream(repository.findAll().spliterator(), false)
                .map(EntityUtils::dumpString)
                .collect(Collectors.toList());
    }

    /**
     * Update the student from the input data
     *
     * @param studentMap key-value pairs corresponding to the student class
     * @return true if updated; false otherwise
     * @throws NumberFormatException thrown when studentMap contains an invalid number for id, group
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean updateStudent(Map<String, String> studentMap) throws NumberFormatException, ValidationException {
        Student student = fromMap(studentMap);
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

    /**
     * Mark the student as absent on for the given week
     * If week is null or an empty string then the current week is considered
     *
     * @param id   number representing the student id
     * @param week number representing the didactic week
     * @return true if marked as absent; false otherwise
     * @throws NumberFormatException thrown when id string is empty or contains an invalid number or week contains an invalid number
     * @throws ArithmeticException   thrown when week is not between 1-28 or there is no didactic activity in the current week
     */
    public Boolean markStudentAbsent(String id, String week) throws NumberFormatException, ArithmeticException {
        if (week == null || week.isEmpty()) {
            week = weekUtils.getCurrentDidacticWeek().toString();
        }
        if (Integer.valueOf(week) > weekUtils.getCurrentDidacticWeek()) {
            return false;
        }
        Student student = repository.findOne(Integer.valueOf(id));
        if (student != null) {
            Student updatedStudent = EntityUtils.clone(student, new Student());
            if (updatedStudent != null) {
                BigInteger absences = updatedStudent.getAbsences();
                updatedStudent.setAbsences(absences.setBit(Integer.valueOf(week) - 1));
                return repository.update(updatedStudent) == null;
            }
            return false;
        }
        return false;
    }

    /**
     * Justify the student absence for the given week
     *
     * @param id   number representing the student id
     * @param week number representing the didactic week
     * @return true if absence was justified; false otherwise
     * @throws NumberFormatException thrown when id/week string is empty or contains an invalid number
     * @throws ArithmeticException   thrown when week is not between 1-28
     */
    public Boolean justifyStudentAbsence(String id, String week) throws NumberFormatException, ArithmeticException {
        Student student = repository.findOne(Integer.valueOf(id));
        if (student != null) {
            Student updatedStudent = EntityUtils.clone(student, new Student());
            if (updatedStudent != null) {
                BigInteger justifiedAbsences = updatedStudent.getJustifiedAbsences();
                updatedStudent.setJustifiedAbsences(justifiedAbsences.setBit(Integer.valueOf(week) - 1));
                return repository.update(updatedStudent) == null;
            }
            return false;
        }
        return false;
    }
}
