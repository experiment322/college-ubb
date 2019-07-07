package service;

import domain.Task;
import domain.validator.ValidationException;
import javafx.collections.MapChangeListener;
import repository.CrudRepository;
import utils.EntityUtils;
import utils.NumberUtils;
import utils.WeekUtils;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class TaskService {
    private WeekUtils weekUtils;
    private CrudRepository<Integer, Task> repository;

    public TaskService(WeekUtils weekUtils, CrudRepository<Integer, Task> repository) {
        this.weekUtils = weekUtils;
        this.repository = repository;
    }

    private void fillDefaults(Map<String, String> taskMap) {
        if (!taskMap.containsKey("assignmentWeek") || taskMap.get("assignmentWeek").isEmpty()) {
            taskMap.put("assignmentWeek", weekUtils.getCurrentDidacticWeek().toString());
        }
    }

    private Task fromMap(Map<String, String> taskMap) {
        fillDefaults(taskMap);
        Task task = new Task();
        task.setId(NumberUtils.tryParseInteger(taskMap.get("id")));
        task.setAssignmentWeek(NumberUtils.tryParseInteger(taskMap.get("assignmentWeek")));
        task.setDeadlineWeek(NumberUtils.tryParseInteger(taskMap.get("deadlineWeek")));
        task.setDescription(taskMap.get("description"));
        return task;
    }

    public void watchRepositoryChanges(MapChangeListener<Integer, Task> handler) {
        repository.observeChanges(handler);
    }

    public WeekUtils getWeekUtils() {
        return weekUtils;
    }

    /**
     * Create a new task from the input data
     *
     * @param taskMap key-value pairs corresponding to the task class
     * @return true if saved; false otherwise
     * @throws NumberFormatException thrown when taskMap contains an invalid number for id, deadlineWeek, assignmentWeek
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean createTask(Map<String, String> taskMap) throws NumberFormatException, ValidationException {
        Task task = fromMap(taskMap);
        return repository.save(task) == null;
    }

    /**
     * Read the task with the given id
     *
     * @param id number representing the task id
     * @return found task as string; empty string otherwise
     * @throws NumberFormatException thrown when id string is empty or contains an invalid number
     */
    public String readOneTask(String id) throws NumberFormatException {
        Task task = repository.findOne(Integer.valueOf(id));
        return task != null ? EntityUtils.dumpString(task) : "";
    }

    /**
     * Read all tasks
     *
     * @return a string list of all tasks
     */
    public List<String> readAllTasks() {
        return StreamSupport.stream(repository.findAll().spliterator(), false)
                .map(EntityUtils::dumpString)
                .collect(Collectors.toList());
    }

    /**
     * Update the task from the input data
     *
     * @param taskMap key-value pairs corresponding to the task class
     * @return true if updated; false otherwise
     * @throws NumberFormatException thrown when taskMap contains an invalid number for id, deadlineWeek, assignmentWeek
     * @throws ValidationException   thrown when at least one value is invalid
     */
    public Boolean updateTask(Map<String, String> taskMap) throws NumberFormatException, ValidationException {
        Task task = fromMap(taskMap);
        return repository.update(task) == null;
    }

    /**
     * Delete the task with the given id
     *
     * @param id number representing the task id
     * @return true if task is found and deleted; false otherwise
     * @throws NumberFormatException thrown when id string is empty or contains an invalid number
     */
    public Boolean deleteTask(String id) throws NumberFormatException {
        return repository.delete(Integer.valueOf(id)) != null;
    }

    /**
     * Extend the task's deadline if it isn't due yet
     *
     * @param taskId          id of the task
     * @param newDeadlineWeek week number
     * @return true if updated; false otherwise
     * @throws NumberFormatException thrown when taskId is not a valid number
     * @throws ValidationException   thrown when the new deadline is invalid
     */
    public Boolean extendTaskDeadline(String taskId, String newDeadlineWeek) throws NumberFormatException, ValidationException {
        Task task = repository.findOne(Integer.valueOf(taskId));
        if (task != null) {
            Task updatedTask = EntityUtils.clone(task, new Task());
            if (updatedTask != null) {
                updatedTask.setDeadlineWeek(Integer.valueOf(newDeadlineWeek));
                return repository.update(updatedTask) == null;
            }
            return false;
        }
        return false;
    }
}
