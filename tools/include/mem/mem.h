/* mem.h */
#ifndef FILE_SORTER_TERMINAL_TOOL_MEM_H
#define FILE_SORTER_TERMINAL_TOOL_MEM_H

#include <stdlib.h>

#define OUT_OF_MEMORY_ERROR -1

#define ALLOCATE_MEMORY(VAR, SIZE, SIZEOF_TYPE) do {                \
        VAR = calloc(SIZE, SIZEOF_TYPE);                            \
        if (VAR == NULL) exit(OUT_OF_MEMORY_ERROR);                 \
    } while(0)

#define REALLOCATE_MEMORY(VAR, NEW_SIZE, SIZEOF_TYPE) do {          \
        VAR = realloc(VAR, NEW_SIZE * SIZEOF_TYPE);                 \
        if (VAR == NULL) exit(OUT_OF_MEMORY_ERROR);                 \
    } while(0)

#define FREE_ARRAY(ARRAY, SIZE) do {                                \
        for (int index = 0; index < SIZE; index++)                  \
            free(ARRAY[index]);                                     \
        free(ARRAY);                                                \
    } while(0)

#endif