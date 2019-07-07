#include "list.h"
#include "util/misc.h"

typedef struct _List {
    int size;
    void ** array;
    void * (* data_cloner)(void * data);
    void (* data_destroyer)(void * data);
} List;

List * create_list(void * (* data_cloner)(void * data), void (* data_destroyer)(void * data)) {
    List * list = safe_malloc(sizeof (*list));
    list->size = 0;
    list->array = NULL;
    list->data_cloner = data_cloner;
    list->data_destroyer = data_destroyer;
    return list;
}

List * clone_list(List * list) {
    int i;
    List * clone = safe_malloc(sizeof (*clone));
    clone->size = list->size;
    clone->array = safe_malloc((size_t)clone->size * sizeof (*clone->array));
    for (i = 0; i < clone->size; ++i) {
        clone->array[i] = list->data_cloner(list->array[i]);
    }
    clone->data_cloner = list->data_cloner;
    clone->data_destroyer = list->data_destroyer;
    return clone;
}

void destroy_list(List * list) {
    int i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->size; ++i) {
        list->data_destroyer(list->array[i]);
    }
    safe_free(list->array);
    safe_free(list);
}

int list_size(List * list) {
    return list->size;
}

void list_add(List * list, void * data) {
    list->array = safe_realloc(list->array, ((size_t)list->size + 1) * sizeof (*list->array));
    list->array[list->size] = data;
    list->size += 1;
}

void * list_set(List * list, int index, void * data) {
    void * old_data = NULL;
    if (-1 < index && index < list->size) {
        old_data = list->array[index];
        list->array[index] = data;
    }
    return old_data;
}

void * list_get(List * list, int index) {
    void * data = NULL;
    if (-1 < index && index < list->size) {
        data = list->array[index];
    }
    return data;
}

void * list_pop(List * list, int index) {
    int i;
    void * data = NULL;
    if (-1 < index && index < list->size) {
        data = list->array[index];
        for (i = index; i < list->size - 1; ++i) {
            list->array[i] = list->array[i + 1];
        }
        list->array = safe_realloc(list->array, ((size_t)list->size - 1) * sizeof (*list->array));
        list->size -= 1;
    }
    return data;
}
