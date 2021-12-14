
#include <stdbool.h>
#include "lib/vector.h"

#ifndef LIB_STACK 

typedef vector_t stack_t;
#define STACK_INIT_SIZE 0x20

#define stack_init vector_init
#define stack_destruction vector_destruction
#define stack_push vector_push
#define stack_pop vector_pop

extern bool stack_is_empty(stack_t *this);



#define LIB_STACK
#endif // LIB_STACK