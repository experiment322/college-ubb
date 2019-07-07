#pragma once
#include "List.h"

/**
	CompareFunc is a pointer to a function that takes two ElementType's 
	and returns  less than zero if e1 is smaller than e2, 0 if they are equal and greater that 0 if 
	e1 is bigger that e2
*/
typedef int(*CompareFunc)(ElementType e1, ElementType e2);

/**
The function sorts in place the elemenets of a list comparing them using the compareFunc pointer function.
*/
void selectionSort(List* list, CompareFunc compareFunc);