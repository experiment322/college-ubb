#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "ListTest.h"
#include "Utils/List.h"

TestStruct* createTestStruct(int x) {
    TestStruct* testS = malloc(sizeof(TestStruct));
     testS->x = x;
    return testS;
}

void destroyFunc(TestStruct* something) {
    free(something);
}

TestStruct* deepCopy(TestStruct* something) {
    return createTestStruct(something->x);
}

void testResize() {
    List* list2 = createList((DestructFunc)destroyFunc, sizeof(TestStruct*));
    addToList(list2, createTestStruct(2));
    addToList(list2, createTestStruct(4));
    addToList(list2, createTestStruct(2));
    addToList(list2, createTestStruct(4));
    addToList(list2, createTestStruct(2));
    addToList(list2, createTestStruct(4));

    assert(((TestStruct*)getAtListIndex(list2, 5))->x == 4);

    destroyList(list2);
}

void runListTests() {
    testResize();
    TestStruct * elem;
    List* list = createList((DestructFunc)destroyFunc, sizeof(TestStruct*));

    assert(getListSize(list) == 0);
    assert(popAtListIndex(list, 0) == NULL);
    addToList(list, createTestStruct(2));
    addToList(list, createTestStruct(4));

    elem = popAtListIndex(list, 0);
    assert(elem != NULL);
    addToList(list, elem);
    elem = popAtListIndex(list, 0);
    assert(elem != NULL);
    addToList(list, elem);

    assert(getListSize(list) == 2);
    assert(((TestStruct*)getAtListIndex(list, 0))->x == 2);
    assert(((TestStruct*)getAtListIndex(list, 1))->x == 4);

    List* list2 = deepCopyList(list, (DeepCopyElementFunc)deepCopy);

    destroyList(list);

    assert(getListSize(list2) == 2);
    assert(((TestStruct*)getAtListIndex(list2, 0))->x == 2);
    assert(((TestStruct*)getAtListIndex(list2, 1))->x == 4);

    // //test if works with a lot of data
    addToList(list2, createTestStruct(2));
    addToList(list2, createTestStruct(4));
    addToList(list2, createTestStruct(2));
    addToList(list2, createTestStruct(4));
    addToList(list2, createTestStruct(2));
    assert(((TestStruct*)getAtListIndex(list2, 5))->x == 4);

    destroyList(list2);
}
