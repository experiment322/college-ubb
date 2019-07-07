package model;

import java.util.List;

public class BubbleSorter implements AbstractSorter {
    private void bubbleSort(List<Integer> integers) {
        Boolean flag = true;
        while (flag) {
            flag = false;
            for (Integer j = 0; j < integers.size() - 1; ++j) {
                if (integers.get(j) > integers.get(j + 1)) {
                    Integer temp = integers.get(j);
                    integers.set(j, integers.get(j + 1));
                    integers.set(j + 1, temp);
                    flag = true;
                }
            }
        }
    }

    @Override
    public void sort(List<Integer> integers) {
        bubbleSort(integers);
    }
}
