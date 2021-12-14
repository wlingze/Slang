

#include "vm/gc/gc.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

object_t *gc_pool_malloc(pool_t *this, int size);

object_t * gc_malloc(int size){
    
    object_t *object;
    if (size <= SMALL_SIZE){
        object = gc_pool_malloc(&small_pool, size);
    } else {
        object = gc_pool_malloc(&large_pool, size);
    }

    if (object != NULL){
        return object;
    }

    gc_start();

    if (size <= SMALL_SIZE){
        object = gc_pool_malloc(&small_pool, size);
    } else {
        object = gc_pool_malloc(&large_pool, size);
    }


    if (object == NULL){
        fprintf(stderr, "gc failed!\n");
        exit(-1);
    }

    return object;
}


object_t *gc_pool_malloc(pool_t *this, int size){
    assert(size < this->size);

    object_t *object = this->object_list;
    if (object == NULL){
        return NULL;
    }

    this->object_list = object->next;
    object->flag = GC_MALLOC_MAGIC;

    object->next = malloc_object_list;
    malloc_object_list = object;
} 

void gc_pool_free(pool_t *this, object_t* object){
    memset(object, 0, sizeof(object));
    object->flag = GC_FREE_MAGIC;
    object->next = this->object_list;
    this->object_list = object->next;
}

void gc_pool_init(pool_t *this, size_t object_size, void * start_addr, void * end_addr){
    this->min_addr = start_addr;
    this->max_addr = end_addr;
    this->size = object_size;
    for(void *i=start_addr; i<end_addr; i+=object_size){
        gc_pool_free(this, i);
    }
}

int gc_memory_size;

void gc_setup(int object_number){
    int small_count = object_number * 15;
    int large_count = object_number * 1;
    gc_memory_size = small_count * SMALL_SIZE + large_count * LARGE_SIZE;

    void * addr; 
    if(posix_memalign(&addr, CACHE_SIZE, gc_memory_size)){
        fprintf(stderr, "gc setup fail");
        exit(-1);
    }

    void *gc_memory_mini = addr;
    void *gc_memory_mid  = addr + small_count * SMALL_SIZE;
    void *gc_memory_max  = addr + gc_memory_size;

    gc_pool_init(&small_pool, SMALL_SIZE, gc_memory_mini, gc_memory_mid);
    gc_pool_init(&large_pool, LARGE_SIZE, gc_memory_mid, gc_memory_max);
}