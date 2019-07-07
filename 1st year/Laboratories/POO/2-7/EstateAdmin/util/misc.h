#ifndef MISC_H
#define MISC_H

#include <stddef.h>

/*
 * Macro used to indicate the success of an operation throughout the program.
 */
#define SUCCESS 1

/*
 *  Macro used to indicate the failure of an operation throughout the program.
 */
#define FAILURE 0

/*
 * Conventional wrapper around malloc which returns NULL if size is 0.
 * Also, it will call exit(EXIT_FAILURE) if the memory couldn't be allocated.
 */
void * safe_malloc(size_t size);

/*
 * Conventional wrapper around realloc which calls free(ptr) and returns NULL if size is 0.
 * Also, it will call exit(EXIT_FAILURE) if the memory couldn't be reallocated.
 */
void * safe_realloc(void * ptr, size_t size);

/*
 * Wrapper created for symmetry.
 */
void safe_free(void * ptr);

#endif // MISC_H
