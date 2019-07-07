#include <stdio.h>
#include <assert.h>
#include "misc_test.h"
#include "util/misc.h"

static void test_safe_malloc(void) {
    int * x = safe_malloc(sizeof (*x));
    assert(x != NULL);
    safe_free(x);
    assert(safe_malloc(0) == NULL);
}

static void test_safe_realloc(void) {
    int * x = safe_malloc(sizeof (*x));
    x = safe_realloc(x, sizeof (*x) * 2);
    assert(x != NULL);
    assert(safe_realloc(x, 0) == NULL);
}

void run_misc_tests(void) {
    printf("\nmisc_test\n");
    test_safe_malloc(); printf("test_safe_malloc() -> OK\n");
    test_safe_realloc(); printf("test_safe_realloc() -> OK\n");
    printf("\n");
}
