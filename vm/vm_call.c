
#include "file/scom.h"
#include "lib/gift.h"
#include "lib/lambda.h"
#include "vm/runtime.h"
#include "lib/opcode.h"
#include "lib/stack.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#define arg runtime_t*r, lambda_t*l
#define next l,r->rip++ 
#define next_code l,lambda_get_code(next)

#define is_func(func_name) \
    !strcmp(func, (func_name))
void vm_opcode_call(arg){
    char *func = lambda_get_word(next_code);
    u_int64_t arg3 = stack_pop(r->stack);
    u_int64_t arg2 = stack_pop(r->stack);
    u_int64_t arg1 = stack_pop(r->stack);
    u_int64_t ret;

    if (is_func("Rudolph")){
        ret = write(arg1, arg2, arg3);
    }
    if (is_func("Dasher")){
        ret = read(arg1, arg2, arg3);
    }
    if (is_func("Dancer")){
        ret = open(arg1, arg2, arg3);
    }
    stack_push(r->stack, ret);
}
#undef is_func

void vm_opcode_load_word(arg){
    char * word = lambda_get_word(next_code);
    u_int64_t item = runtime_get_gift(r, word);
    if (item < 0){
        printf("error: '%s' undeclared \n", word);
        exit(EXIT_FAILURE);
    }
    stack_push(r->stack, (u_int64_t)item);
}

void vm_opcode_load_string(arg){
    char * str = lambda_get_string(next_code);
    stack_push(r->stack, (u_int64_t)str);
}

void vm_opcode_load_number(arg){
    int number = lambda_get_number(next_code);
    stack_push(r->stack, number);
}

void vm_opcode_store(runtime_t *r, lambda_t *l){
    u_int64_t item =  stack_pop(r->stack);
    char * name = lambda_get_word(next_code);
    gift_t *gift = gift_init(name, item);
    vector_push_back(&(r->gifts), gift);
}

void check_next(arg){
    if (r->rip >= l->code.count)
        r->is_run = 0;
}

#define display(OPCODE, opcode)                                                \
  case OP_##OPCODE:                                                            \
    vm_opcode_##opcode(r, l);                                                  \
    break

void vm_call_lambda(lambda_t *l){
    runtime_t *r = runtime_init();


    while(r->is_run){
        switch(lambda_get_code(next)){
            display(LOAD_NUMBER, load_number);
            display(LOAD_STRING, load_string);
            display(LOAD_WORD, load_word);
            display(STORE, store);
            display(CALL, call);
        }
        check_next(r, l);
    }

}
#undef arg