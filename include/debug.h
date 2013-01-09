#pragma once
#ifdef DEBUG
    #ifndef DEBUG_VERBOSE
        #define DEBUG_VERBOSE 2
    #endif

extern int alloc_counter;
extern void *debug_malloc(size_t size);
extern void debug_free(void *ptr);
extern int debug_num_allocs();

#if DEBUG_VERBOSE == 1
    #define malloc(size) debug_malloc(size); debug_num_allocs()
    #define free(ptr) debug_free(ptr); debug_num_allocs()
#elif DEBUG_VERBOSE == 2
    #define malloc(size) debug_malloc(size); printf("Alloc %d: Line %d of File %s\n", alloc_counter, __LINE__, __FILE__)
    #define free(ptr) debug_free(ptr); printf("Free %d: Line %d of File %s\n", alloc_counter, __LINE__, __FILE__)
#else
    #define malloc(size) debug_malloc(size)
    #define free(ptr) debug_free(ptr)
#endif

#endif