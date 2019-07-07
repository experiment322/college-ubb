#include "Utils/List.h"
#include "Utils/Utils.h"
#include "UtilsTest.h"
#include <stdlib.h>
#include <assert.h>

UtilsStruct* createUtilsStruct(int x) {
    UtilsStruct* testS = malloc(sizeof(UtilsStruct));
    testS->x = x;
    return testS;
}

void destroyFunc2(UtilsStruct* something) {
    free(something);
}

int compareF(UtilsStruct* u1, UtilsStruct* u2) {
    return u1->x - u2->x;
}

void runUtilsTest() {

    List* list = createList((DestructFunc)destroyFunc2, sizeof(UtilsStruct*));

    assert(getListSize(list) == 0);
    addToList(list, createUtilsStruct(2));
    addToList(list, createUtilsStruct(4));
    addToList(list, createUtilsStruct(0));
    selectionSort(list, (CompareFunc)compareF);
    UtilsStruct* utilsStruct = getAtListIndex(list, 0);
    assert(utilsStruct->x == 0);

    destroyList(list);


}
