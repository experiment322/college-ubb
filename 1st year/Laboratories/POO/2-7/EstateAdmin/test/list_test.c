#include <stdio.h>
#include <assert.h>
#include "list_test.h"
#include "util/list.h"
#include "util/misc.h"

static void * create_int(int value) {
    int * n = safe_malloc(sizeof (*n));
    *n = value;
    return n;
}

static void * clone_int(void * n) {
    int * clone = safe_malloc(sizeof (*clone));
    *clone = *(int *)n;
    return clone;
}

static void destroy_int(void * n) {
    safe_free(n);
}

static void test_list_add(void) {
    List * list = create_list(clone_int, destroy_int);
    assert(list_size(list) == 0);
    list_add(list, create_int(1));
    assert(list_size(list) == 1);
    list_add(list, create_int(2));
    assert(list_size(list) == 2);
    destroy_list(list);
}

static void test_list_get(void) {
    int * x = create_int(1);
    int * y = create_int(2);
    List * list = create_list(clone_int, destroy_int);
    assert(list_get(list, list_size(list)) == NULL);
    list_add(list, x);
    assert(*(int *)list_get(list, list_size(list) - 1) == *x);
    list_add(list, y);
    assert(*(int *)list_get(list, list_size(list) - 2) == *x);
    assert(*(int *)list_get(list, list_size(list) - 1) == *y);
    destroy_list(list);
}

static void test_list_set(void) {
    int * x = create_int(1);
    int * y = create_int(2);
    List * list = create_list(clone_int, destroy_int);
    list_add(list, x);
    list_add(list, x);
    assert(*(int *)list_set(list, list_size(list) - 1, y) == *x);
    assert(*(int *)list_get(list, list_size(list) - 2) == *x);
    assert(*(int *)list_get(list, list_size(list) - 1) == *y);
    destroy_list(list);
}

static void test_list_pop(void) {
    int * x = create_int(1);
    int * y = create_int(2);
    List * list = create_list(clone_int, destroy_int);
    list_add(list, x);
    list_add(list, y);
    assert(*(int *)list_pop(list, list_size(list) - 2) == *x);
    assert(*(int *)list_pop(list, list_size(list) - 1) == *y);
    destroy_int(x);
    destroy_int(y);
    destroy_list(list);
}

static void test_clone_list(void) {
    int * x = create_int(1);
    int * y = create_int(2);
    List * clone, * list = create_list(clone_int, destroy_int);
    list_add(list, x);
    list_add(list, y);
    clone = clone_list(list);
    assert(list_get(clone, list_size(clone) - 1) != y);
    assert(list_get(clone, list_size(clone) - 2) != x);
    assert(*(int *)list_get(clone, list_size(clone) - 1) == *y);
    assert(*(int *)list_get(clone, list_size(clone) - 2) == *x);
    destroy_list(list);
    destroy_list(clone);
}

void run_list_tests(void) {
    printf("\nlist_test\n");
    test_list_add(); printf("test_list_add() -> OK\n");
    test_list_get(); printf("test_list_get() -> OK\n");
    test_list_set(); printf("test_list_set() -> OK\n");
    test_list_pop(); printf("test_list_pop() -> OK\n");
    test_clone_list(); printf("test_clone_list() -> OK\n");
    destroy_list(NULL); // for code coverage
    printf("\n");
}
