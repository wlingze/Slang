

#ifndef GC_GC

#include "object/object.h"
#include <stdlib.h>

#define CACHE_SIZE  0x40
#define SMALL_SIZE  CACHE_SIZE
#define LARGE_SIZE  CACHE_SIZE * 4

#define GC_MAGIC        0xffffff00
#define GC_FREE_MAGIC   0x46524500
#define GC_MALLOC_MAGIC 0xb9adbb00


typedef struct pool {
    void * min_addr;
    void * max_addr;
    int size;
    object_t * object_list;
} pool_t;

object_t * malloc_object_list;

pool_t small_pool;
pool_t large_pool;

extern void gc_start();
extern void gc_setup(int object_number);

#define GC_GC 
#endif  // GC_GC