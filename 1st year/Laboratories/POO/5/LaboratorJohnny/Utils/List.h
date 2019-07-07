#pragma once

typedef void(*DestructFunc)(void*);

typedef void*(*DeepCopyElementFunc)(void*);

typedef void* ElementType;

typedef struct {
    int size;
    int capacity;
    ElementType* elements;
    DestructFunc destructFunc;
    int elementSize;
} List;


/**
 *  Functia returneaza un pointer la un List pe heap, struct alocat dinamic
 * @return List alocat dinamic
   @param destryFunc o functie ce se va apela cu un obiect din lista si are menirea de a elibera
   memoria ocupata de entitate
   @param elementSize - dimensiunea elementelor ce se vor salva in lista
 * Postconditii: memoria va fi eliberata apeland destroyList
 */
List* createList(DestructFunc destroyFunc, int elementSize);

/**
 Functia creaza o noua lista in care vor fi copiate deep elementele din lista intiala
 @param list - lista din care se face copierea
 @param deepCopyFunc - functie ce copiaza in adancime entitatile din lista

*/
List* deepCopyList(List* list, DeepCopyElementFunc deepCopyFunc);

/**
 * Functia elibereaza memoria alocata unui List
 * @param List - lista asupra caruia se elibereaza memoria
 *
 * Preconditie: List e o lista creata cu createList
 */
void destroyList(List* List);

/**
 * Returneaza marimiea unei liste date
 * @param list
 * @return un int
 */
int getListSize(List* list);

/**
 * Functia permite iterarea unei liste printr-un index
 * @param list
 * @return un obiect Medicine aflat la un anumit index in lista
 * Preconditie: index este mai mic strict decat marimea listei
 */
void* getAtListIndex(List* list, int index);

/**
 * Functia adauga in lita list pointer-ul la structul medicine
 * @param list
 * @param entity - obiectul ce se adauga in lista
 */
void addToList(List* list, ElementType entity);

/**
 * Functia elimina din lista elementul de la pozitia index
 * @param list
 * @param index
 * @return un obiect Medicine aflat la un anumit index in lista sau NULL daca index-ul este invalid
 * Preconditie: index este mai mic strict decat marimea listei
 */
ElementType popAtListIndex(List * list, int index);
