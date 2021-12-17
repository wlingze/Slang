#ifndef VM_RUNTIME
#define VM_RUNTIME

#include <stdint.h>
#include "lib/gift.h"
#include "lib/vector.h"
#include "lib/stack.h"

typedef struct runtime {
    int64_t rip;
    int64_t r1; 
    int is_run;

    stack_t * stack;
    vector_template(gift_t*, gifts);
} runtime_t;

runtime_t* runtime_init();
u_int64_t runtime_get_gift(runtime_t *this, char *word);
#endif 