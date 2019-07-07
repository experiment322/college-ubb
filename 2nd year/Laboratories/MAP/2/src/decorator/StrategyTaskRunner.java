package decorator;

import decorator.TaskRunner;
import factory.Strategy;
import factory.TaskContainerFactory;
import model.Container;
import model.Task;

public class StrategyTaskRunner implements TaskRunner {

    private Container container;

    public StrategyTaskRunner(Strategy strategy)
    {
        container=TaskContainerFactory.getInstance().createContainer(strategy);
    }
    @Override
    public void executeOneTask() {
        Task task = container.remove();
        task.execute();
    }

    @Override
    public void executeAll() {
        while(!container.isEmpty())
            executeOneTask();
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
