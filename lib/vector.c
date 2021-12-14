
#include "lib/vector.h"
#include <assert.h>
#include <stdlib.h>

void vector_init(vector_t *this){
    this->count = 0;
    this->capacity = VECTOR_INIT_SIZE;
    this->data = malloc(this->capacity * sizeof(void *));
}

void vector_destruction(vector_t *this){
    free(this->data);
}

void vector_push(vector_t *this, void *item){
    if(this->count >= this->capacity){
        this->capacity *= 2;
        unsigned int size = this->capacity * sizeof(void *);
        this->data = realloc(this->data, size);
    }
    this->data[this->count] = item;
    this->count ++;
}


void *vector_pop(vector_t *this){
    void *tmp = this->data[this->count];
    this->data[this->count] = NULL;
    this->count --;
    return tmp;
}

void *vector_get(vector_t *this, unsigned int idx){
    assert(idx < this->count);
    return this->data[idx];
}

void vector_set(vector_t *this, unsigned int idx, void *item){
    assert(idx < this->count);
    this->data[idx] = item;
}