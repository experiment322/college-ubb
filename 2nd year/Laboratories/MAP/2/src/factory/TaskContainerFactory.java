package factory;

import factory.Factory;
import factory.Strategy;
import model.Container;
import model.QueueContainer;
import model.StackContainer;

public class TaskContainerFactory implements Factory {
    private static final TaskContainerFactory singleton = new TaskContainerFactory();

    public static TaskContainerFactory getInstance() {
        return singleton;
    }

    private TaskContainerFactory() {
    }

    @Override
    public Container createContainer(Strategy startegy) {
        if (startegy == Strategy.FIFO)
            return new QueueContainer();
        else
            return new StackContainer();
    }
}
