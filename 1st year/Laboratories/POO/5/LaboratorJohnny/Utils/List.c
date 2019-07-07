//
// Created by ionut on 14.03.2018.
//

#include "List.h"
#include <stdlib.h>
#include <string.h>

int getListSize(List* list) {
    return list->size;
}

ElementType getAtListIndex(List* list, int index) {
    return list->elements[index];
}

ElementType popAtListIndex(List * list, int index) {
    int i;
    ElementType element;
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    list->size -= 1;
    element = list->elements[index];
    for (i = index; i < list->size; ++i) {
        list->elements[i] = list->elements[i + 1];
    }
    list->elements[i + 1] = NULL;
    return element;
}

void addToList(List* list, ElementType element) {
    if (list->capacity == list->size) {
        ElementType* temp = realloc(list->elements, list->capacity * 2 * list->elementSize);
        list->capacity = list->capacity * 2;
        list->elements = temp;

    }
    list->elements[list->size] = element;
    list->size++;
}

List* createList(DestructFunc destructFunc, int elementSize) {
    List* list = malloc(sizeof(List));

    list->size = 0;
    list->capacity = 4;
    list->destructFunc = destructFunc;
    list->elementSize = elementSize;
    list->elements = (void**)malloc(list->capacity * elementSize);
    return list;
}

List* deepCopyList(List* list, DeepCopyElementFunc deepCopyFunc) {
    void* element;
    List* cpList = malloc(sizeof(List));
    cpList->capacity = list->capacity;
    cpList->elementSize = list->elementSize;
    cpList->destructFunc = list->destructFunc;
    cpList->size = 0; // reset counter
                      // size will increment in the addToList function

    cpList->elements = malloc(list->capacity * list->elementSize);
    for (int i = 0; i < getListSize(list); i++) {
        element = getAtListIndex(list, i);
        addToList(cpList, deepCopyFunc(element));
    }

    return cpList;
}

void destroyList(List* list) {
    ElementType element;
    for (int i = 0; i < getListSize(list); i++) {
        element = getAtListIndex(list, i);
        list->destructFunc(element);
    }
    free(list->elements);
    free(list);
}

