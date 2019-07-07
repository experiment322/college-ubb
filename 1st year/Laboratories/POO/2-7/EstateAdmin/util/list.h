#ifndef LIST_H
#define LIST_H

typedef struct _List List;

/*
 * Create a new dynamic list and return a pointer to it.
 * data_cloner is a function that clones the list's elements and is used only in clone_list().
 * data_cloner should create a new element and copy over the properties of the original element.
 * data_destroyer is a function that destroys the lists's elements and is used only in destroy_list().
 * Both get a pointer to an element, i.e. the pointer passed by the developer in list_add().
 */
List * create_list(void * (* data_cloner)(void * data), void (* data_destroyer)(void * data));

/*
 * Clone an existing list by calling data_cloner() for each element.
 * Returns a pointer to the newly created list.
 * It is the responsability of the developer to avoid passing an invalid list as parameter, i.e. NULL.
 */
List * clone_list(List * list);

/*
 * Destroy the list and every element in list by calling data_destroyer() on each one.
 * If NULL is received as a parameter nothing is done.
 */
void destroy_list(List * list);

/*
 * Returns the number of elements the list contains.
 */
int list_size(List * list);

/*
 * Adds data to the list, which is a pointer to a structure allocated by the developer.
 * The data is not cloned and if it is freed outside of the list then the list will contain a dangling pointer.
 */
void list_add(List * list, void * data);

/*
 * Replace the data at index with the data given in the parameters.
 * If the index is out of the list's range, then NULL is returned and data is not added to the list.
 * Otherwise place data at the given index and return the old data.
 */
void * list_set(List * list, int index, void * data);

/*
 * Return the element at the given index, but it isn't removed from the list.
 * If index is out of range return NULL.
 * Do not destroy the returned element, otherwise the list will contain a dangling pointer.
 * Also note that any modification to it will reflect in the list.
 */
void * list_get(List * list, int index);

/*
 * Return the element at the given index by removing it from the list, thus decreasing the list size by 1.
 * If the index is out of range return NULL and do nothing.
 */
void * list_pop(List * list, int index);

#endif // LIST_H
