#include <stdlib.h>
#include "misc.h"

#define EXITIFNULL(PTR, SIZE) if ((PTR) == NULL && (SIZE)) exit(EXIT_FAILURE)

void * safe_malloc(size_t size) {
    void * p = size ? malloc(size) : NULL;
    EXITIFNULL(p, size);
    return p;
}

void * safe_realloc(void * ptr, size_t size) {
    void * p = size ? realloc(ptr, size) : NULL;
    if (!size) {
        free(ptr);
    }
    EXITIFNULL(p, size);
    return p;
}

void safe_free(void * ptr) {
    free(ptr);
}
