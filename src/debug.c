#include <stdio.h>
#include <stdlib.h>

int alloc_counter = 0;

void *debug_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr) alloc_counter++;
    return ptr;
}

void debug_free(void *ptr)
{
    free(ptr);
    alloc_counter--;
}

int debug_num_allocs()
{
    printf("Alloc Counter: %d\n", alloc_counter);
    return alloc_counter;
}
