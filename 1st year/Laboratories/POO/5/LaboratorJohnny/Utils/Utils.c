#include "Utils.h"


void selectionSort(List* list, CompareFunc compareFunc) {
	ElementType min, aux;
	int minPos;
	for (int i = 0; i < getListSize(list) - 1; i++) {
		// lower that min, new min
		min = list->elements[i];
		aux = list->elements[i];
		minPos = i;
		for (int j = i + 1; j < getListSize(list); j++) {
			if (compareFunc(getAtListIndex(list, j), min) <= 0) {
				min = getAtListIndex(list, j);
				minPos = j;
			}
		}
		list->elements[i] = min;
		list->elements[minPos] = aux;
	}
}