package model;

public class StackContainer extends Container {
    @Override
    public Task remove() {
        if (!tasks.isEmpty())
            return tasks.remove(tasks.size() - 1);
        else
            return null;
    }
}
