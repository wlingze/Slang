
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

#define get_code        lambda_get_code(next)
#define get_word        lambda_get_word(l, get_code)
#define get_number      lambda_get_number(l, get_code)
#define get_string      lambda_get_string(l, get_code)
#define pop             stack_pop(r->stack)
#define push(item)      stack_push(r->stack, (u_int64_t)(item))
#define get_gift(word)      runtime_get_gift(r, (word))

char * rudolph = "Rudolph has been with Santa. \nGoing to deliver presents soon!\nYou can't get him to help. \nQaQ";


void vm_opcode_store(runtime_t *r, lambda_t *l){
    u_int64_t item =  pop;
    char * name = get_word;
    gift_t *gift = get_gift(name);
    if (!gift){
        gift = gift_init(name, item);
        runtime_set_gift(r, gift);
    } else {
        gift->item = item;
    }
}


void vm_opcode_load_word(arg){
    char * word = get_word;
    gift_t* gift = get_gift(word);
    if (!gift){
        printf("error: '%s' undeclared \n", word);
        exit(EXIT_FAILURE);
    }
    push(gift->item);
}

void vm_opcode_load_string(arg){
    push(get_string);
}

void vm_opcode_load_number(arg){
    push(get_number);
}
#define is_func(func_name) \
    !strcmp(func, (func_name))
void vm_opcode_call(arg){
    char *func = get_word;
    u_int64_t arg3 = pop;
    u_int64_t arg2 = pop;
    u_int64_t arg1 = pop;
    u_int64_t ret;

    if (is_func("Rudolph")){
        ret = write(arg1, arg2, arg3);
        // printf("error: \n%s", rudolph);
    }
    if (is_func("Dasher")){
        ret = read(arg1, arg2, arg3);
    }
    if (is_func("Dancer")){
        ret = open(arg1, arg2, arg3);
    }
    if (is_func("Prancer")){
        ret = strncmp(arg1, arg2, arg3);
    }
    push(ret);
}
#undef is_func

void vm_opcode_jmp(arg){
    int direction = get_code;
    int offset = 0;
    offset = (get_code << 8) | get_code;
    if (direction == J_FORWORD){
        r->rip += offset;
    } else {
        r->rip -= offset;
    }
}
void vm_opcode_jz(arg){
    u_int64_t is_not_jmp = pop;
    if (is_not_jmp){
        r->rip += 3;
    } else {
        vm_opcode_jmp(r, l);
    }
}

void vm_opcode_operator(arg, int opcode){
    u_int64_t a = pop;
    u_int64_t b = pop;
    switch (opcode){
        case OP_ADD:
            push(b+a);
            break;
        case OP_SUB:
            push(b-a);
            break;
        case OP_MUL:
            push(b*a);
            break;
        case OP_DIV:
            push(b/a);
            break;
        case OP_GRAETER:
            push(b>a);
            break;
        case OP_EQUAL:
            push(b==a);
            break;
    }
}

void check_next(arg){
    if (r->rip >= l->code.count)
        r->is_run = 0;
}

#define display(OPCODE, opcode)                                                \
  case OP_##OPCODE:                                                            \
    vm_opcode_##opcode(r, l);                                                  \
    break

#define operator(OPCODE)                                                \
  case OP_##OPCODE:                                                            \
    vm_opcode_operator(r, l, OP_##OPCODE);                                                  \
    break
void vm_call_lambda(lambda_t *l){
    runtime_t *r = runtime_init();

    while(r->is_run){
        switch(lambda_get_code(next)){
            display(STORE, store);
            display(LOAD_NUMBER, load_number);
            display(LOAD_STRING, load_string);
            display(LOAD_WORD, load_word);

            display(CALL, call);
            display(JZ, jz);
            display(JMP, jmp);

            operator(ADD);
            operator(SUB);
            operator(DIV);
            operator(MUL);
            operator(GRAETER);
            operator(EQUAL);
        }
        check_next(r, l);
    }

}

#undef arg
#undef get_code        
#undef get_word        
#undef get_number      
#undef get_string      
#undef pop             
#undef push
#undef gift