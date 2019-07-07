package model;

public class QueueContainer extends Container {
    @Override
    public Task remove() {
        if (!tasks.isEmpty())
            return tasks.remove(0);
        else
            return null;
    }
}
