
#include "lib/stack.h"
#include <sys/types.h>
#include <stddef.h>
#include <stdlib.h>

stack_t * stack_init(){
    stack_t *this = malloc(sizeof(stack_t));
    this->count = 0;
    this->capacity = 0;
    this->data = NULL;
    return this;
}

#define pthis stack_t *this

u_int64_t stack_pop(pthis){
    u_int64_t tmp = this->data[this->count-1];
    this->data[this->count] = 0;
    this->count --;
    return tmp;
}


void stack_push(pthis, u_int64_t item){
    if (this->capacity == 0){
        this->capacity = 2;
        this->data = malloc(this->capacity * 0x10);
    }
    if (this->count >= this->capacity) {
        this->capacity *= 2;
        this->data = realloc(this->data, this->capacity * 0x10);
    }

    this->data[this->count] = item;
    this->count ++;
}

bool stack_is_empty(pthis){
    return this->count == 0;
}
#undef pthis