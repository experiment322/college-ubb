package model;

import java.util.ArrayList;
import java.util.List;

public abstract class Container {
    List<Task> tasks = new ArrayList<>();

    public abstract Task remove();

    public void add(Task task) {
        tasks.add(task);
    }

    public Integer size() {
        return tasks.size();
    }

    public Boolean isEmpty() {
        return tasks.size() == 0;
    }
}
