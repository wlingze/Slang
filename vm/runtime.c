
#include "vm/runtime.h"
#include <sys/types.h>
#include <stdlib.h>

runtime_t* runtime_init(){
    runtime_t *this = malloc(sizeof(runtime_t));

    vector_init(&(this->gifts));
    this->stack = stack_init();
    this->r1 = 0;
    this->rip = 0;
    this->is_run = 1;
    return this;
}

#define pthis runtime_t *this

u_int64_t runtime_get_gift(pthis, char *word){
    int i = 0;
    gift_t *item;
    vector_each(this->gifts, i, item){
        if (!strcmp(item->name, word)){
            return item->item;
        }
    }
    return -1;
}

#undef pthis