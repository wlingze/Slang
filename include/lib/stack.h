
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include "lib/vector.h"

#ifndef LIB_STACK 
#define LIB_STACK

typedef struct stack {
    unsigned int count;
    unsigned int capacity;
    u_int64_t *data;
} stack_t ;
#define STACK_INIT_SIZE 0x20

#define stack_destruction vector_destruction

extern bool stack_is_empty(stack_t *this);
stack_t * stack_init();

void stack_push(stack_t *this, u_int64_t item);
u_int64_t stack_pop(stack_t *this);


#endif // LIB_STACK