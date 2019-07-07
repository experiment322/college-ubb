package model;

import java.util.List;

public class QuickSorter implements AbstractSorter {
    private void quickSort(List<Integer> integers, Integer low, Integer high) {
        if (integers == null || integers.size() == 0) return;
        if (low >= high) return;

        Integer middle = low + (high - low) / 2;
        Integer pivot = integers.get(middle);

        Integer i = low;
        Integer j = high;
        while (i <= j) {
            while (integers.get(i) < pivot) ++i;
            while (integers.get(j) > pivot) --j;
            if (i <= j) {
                Integer temp = integers.get(i);
                integers.set(i, integers.get(j));
                integers.set(j, temp);
                ++i;
                --j;
            }
        }

        if (low < j) quickSort(integers, low, j);
        if (high > i) quickSort(integers, i, high);
    }

    @Override
    public void sort(List<Integer> integers) {
        quickSort(integers, 0, integers.size());
    }
}
