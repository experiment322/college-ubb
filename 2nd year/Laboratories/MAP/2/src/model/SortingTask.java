package model;

import java.util.List;

public class SortingTask extends Task {
    private List<Integer> integers;
    private AbstractSorter abstractSorter;

    public SortingTask(String taskId, String descriere, List<Integer> integers, AbstractSorter abstractSorter) {
        super(taskId, descriere);
        this.integers = integers;
        this.abstractSorter = abstractSorter;
    }

    @Override
    public void execute() {
        abstractSorter.sort(integers);
        for (Integer integer : integers) {
            System.out.println(integer);
        }
    }
}
