package service;

import domain.Mark;
import domain.Student;
import domain.Task;
import domain.validator.ValidationException;
import javafx.collections.MapChangeListener;
import repository.CrudRepository;
import utils.EntityUtils;
import utils.NumberUtils;
import utils.WeekUtils;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.StreamSupport;

public class MarkService {
    private WeekUtils weekUtils;
    private CrudRepository<String, Mark> repository;
    private CrudRepository<Integer, Task> taskRepository;
    private CrudRepository<Integer, Student> studentRepository;

    public MarkService(WeekUtils weekUtils,
                       CrudRepository<String, Mark> repository,
                       CrudRepository<Integer, Task> taskRepository,
                       CrudRepository<Integer, Student> studentRepository) {
        this.weekUtils = weekUtils;
        this.repository = repository;
        this.taskRepository = taskRepository;
        this.studentRepository = studentRepository;
    }

    private void fillDefaults(Map<String, String> markMap) {
        if (!markMap.containsKey("feedback") || markMap.get("feedback").isEmpty()) {
            markMap.put("feedback", "NO FEEDBACK");
        }
        if (!markMap.containsKey("week") || markMap.get("week").isEmpty()) {
            markMap.put("week", weekUtils.getCurrentDidacticWeek().toString());
        }
    }

    private Mark fromMap(Map<String, String> markMap) {
        fillDefaults(markMap);
        Mark mark = new Mark();
        mark.setId(
                NumberUtils.tryParseInteger(markMap.get("taskId")),
                NumberUtils.tryParseInteger(markMap.get("studentId"))
        );
        mark.setValue(NumberUtils.tryParseDouble(markMap.get("value")));
        mark.setWeek(NumberUtils.tryParseInteger(markMap.get("week")));
        mark.setFeedback(markMap.get("feedback"));
        return mark;
    }

    public void watchRepositoryChanges(MapChangeListener<String, Mark> handler) {
        repository.observeChanges(handler);
    }

    public WeekUtils getWeekUtils() {
        return weekUtils;
    }

    /**
     * Checks if there is a task and a student having the ids associated to the given markMap
     * Also checks if the mark is given after the deadline week (inclusive) and if the student is present in that week
     *
     * @param markMap key-value pairs corresponding to the mark class
     * @return true if the above conditions are met; false otherwise
     * @throws NumberFormatException thrown when markMap contains an invalid number for studentId, taskId, value or week
     */
    private Boolean canGiveMark(Map<String, String> markMap) throws NumberFormatException {
        Mark mark = fromMap(markMap);
        Task task = taskRepository.findOne(mark.getTaskId());
        Student student = studentRepository.findOne(mark.getStudentId());
        if (task == null || student == null) {
            return false;
        }
        return mark.getWeek() >= task.getDeadlineWeek() && (
                !student.getAbsences().testBit(mark.getWeek() - 1)
                        || student.getJustifiedAbsences().testBit(mark.getWeek() - 1)
        );
    }

    /**
     * Get the maximum possible mark value for the input data
     * The value is calculated by subtracting 2.5 points from 10 for every delayed week
     * If the delayed weeks exceed two it will return null because the student cannot receive a mark anymore
     * The student can still receive a mark if it has enough justified absences between the deadline week (inclusive) and mark's week (exclusive)
     * null is also returned if canGiveMark returns false for the given mark
     *
     * @param markMap key-value pairs corresponding to the mark class
     * @return maximum mark value (between 5.0 and 10.0); null if the mark cannot be given
     * @throws NumberFormatException thrown when markMap contains an invalid number for studentId, taskId, value or week
     */
    public Double getMaximumMarkValue(Map<String, String> markMap) throws NumberFormatException {
        if (!canGiveMark(markMap)) {
            return null;
        }
        Mark mark = fromMap(markMap);
        Integer assignmentDelay = computeAssignmentDelay(mark);
        if (assignmentDelay > 2) {
            return null;
        }
        return 10.0 - (assignmentDelay * 2.5);
    }

    private Integer computeAssignmentDelay(Mark mark) {
        Task task = taskRepository.findOne(mark.getTaskId());
        Student student = studentRepository.findOne(mark.getStudentId());

        // The actual checked range is task.deadlineWeek (inclusive) to mark.week - 1 (inclusive)
        // It is shifted with -1 because bits are indexed from 0
        Integer justifiedAbsenceCount = IntStream.rangeClosed(task.getDeadlineWeek() - 1, mark.getWeek() - 2)
                .filter(student.getJustifiedAbsences()::testBit)
                .map(operand -> 1)
                .sum();
        return mark.getWeek() - (task.getDeadlineWeek() + justifiedAbsenceCount);
    }

    /**
     * Create a new mark from the input data
     * Maximum mark value is given by calling getMaximumMarkValue for the given mark
     * false is returned prematurely if getMaximumMarkValue returns null
     *
     * @param markMap key-value pairs corresponding to the mark class
     * @return true if saved; false otherwise
     * @throws NumberFormatException thrown when markMap contains an invalid number for studentId, taskId, value or week
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean createMark(Map<String, String> markMap) throws NumberFormatException, ValidationException {
        Double maximumMarkValue = getMaximumMarkValue(markMap);
        if (maximumMarkValue == null) {
            return false;
        }
        Mark mark = fromMap(markMap);
        mark.setValue(Math.min(maximumMarkValue, mark.getValue()));
        return repository.save(mark) == null;
    }

    /**
     * Read all marks
     *
     * @return a string list of all marks
     */
    public List<String> readAllMarks() {
        return StreamSupport.stream(repository.findAll().spliterator(), false)
                .map(EntityUtils::dumpString)
                .collect(Collectors.toList());
    }

    /**
     * Save useful mark info to a file named after the associated student
     * Only studentId and taskId are used from the markMap because the map is retrieved from the repository
     *
     * @param markMap key-value pairs corresponding to the mark class
     * @return true if no IO error was encountered; false otherwise
     * @throws NumberFormatException thrown when markMap contains an invalid number for studentId, taskId
     */
    public Boolean dumpMarkToStudentFile(Map<String, String> markMap) throws NumberFormatException {
        Mark tempMark = new Mark();
        tempMark.setId(
                Integer.valueOf(markMap.get("taskId")),
                Integer.valueOf(markMap.get("studentId"))
        );
        Mark mark = repository.findOne(tempMark.getId());
        if (mark != null) {
            Path path = getDumpPath(mark);
            try {
                Files.write(
                        path,
                        Collections.singletonList(getDumpInfo(mark)),
                        Files.exists(path) ? StandardOpenOption.APPEND : StandardOpenOption.CREATE
                );
                return true;
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }
        }
        return false;
    }

    private Path getDumpPath(Mark mark) {
        Student student = studentRepository.findOne(mark.getStudentId());
        String studentName = student.getName().replaceAll("\\s+", "");
        return Paths.get(studentName + "_" + student.getId() + ".txt");
    }

    private String getDumpInfo(Mark mark) {
        Student student = studentRepository.findOne(mark.getStudentId());
        Task task = taskRepository.findOne(mark.getTaskId());
        String absences = student.getAbsences().toString(2).replace("", " ").trim();
        String justified = student.getJustifiedAbsences().toString(2).replace("", " ").trim();
        Function<String, String> pad = s -> String.format("%-16s", s);
        return pad.apply("Task:") + task.getId() + System.lineSeparator() +
                pad.apply("Deadline:") + task.getDeadlineWeek() + System.lineSeparator() +
                pad.apply("Handed:") + mark.getWeek() + System.lineSeparator() +
                pad.apply("Mark:") + mark.getValue() + System.lineSeparator() +
                pad.apply("Feedback:") + mark.getFeedback() + System.lineSeparator() +
                pad.apply("Absences:") + new StringBuilder(absences).reverse().toString() + System.lineSeparator() +
                pad.apply("Justified:") + new StringBuilder(justified).reverse().toString() + System.lineSeparator();
    }
}
