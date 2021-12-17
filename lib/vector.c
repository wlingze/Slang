
#include "lib/vector.h"
#include <assert.h>
#include <stdlib.h>

void vector_destruction(vector_t *this){
    free(this->data);
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