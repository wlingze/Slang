
#include "disasm/line.h"
#include "lib/lambda.h"
#include "disasm/disasm.h"
#include "lib/opcode.h"
#include "vm/runtime.h"
#include <sys/types.h>
#include <stdio.h>

#define arg line_t *r, lambda_t*l
#define next l,r->rip++ 
#define get_code        lambda_get_code(next)
#define get_word        lambda_get_word(l, get_code)
#define get_number      lambda_get_number(l, get_code)
#define get_string      lambda_get_string(l, get_code)


void disasm_store(arg){
    output(r->rip-2, "pop\t%s", get_word);
}

void disasm_load_number(arg){
    output(r->rip-2, "push\t%d", get_number);
}

void disasm_load_string(arg){
    output(r->rip-2, "push\t\"%s\"", get_string);
}

void disasm_load_word(arg){
    output(r->rip-2, "push\t%s", get_word);
}

#define is_func(func_name) \
    !strcmp(func, (func_name))
void disasm_call(arg){
    char *func = get_word;
    output(r->rip-2, "call\t%s", func);
}
#undef is_func

int jmp_target(arg){
    int direction = get_code;
    int offset = 0;
    offset = (get_code << 8) | get_code;
    int target = r->rip;
    if (direction == J_FORWORD){
        target += offset;
    } else {
        target -= offset;
    }
    line_jmp(r, target);
    return target;
}
void disasm_jz(arg){
    output(r->rip-4, "jz\t%d\n", jmp_target(r, l));
}

void disasm_jmp(arg){
    output(r->rip-4, "jmp\t%d\n", jmp_target(r, l));
}

void disasm_operator(arg, int opcode){
    switch (opcode){
        case OP_ADD:
            output(r->rip-1, "add");
            break;
        case OP_SUB:
            output(r->rip-1, "sub");
            break;
        case OP_MUL:
            output(r->rip-1, "mul");
            break;
        case OP_DIV:
            output(r->rip-1, "div");
            break;
        case OP_GRAETER:
            output(r->rip-1, "graeter");
            break;
        case OP_EQUAL:
            output(r->rip-1, "equal");
            break;
    }
}

void check_next_line(line_t *r, lambda_t * l){
    if (r->rip >= l->code.count)
        r->is_run = 0;
}

#define display(OPCODE, opcode)                                         \
  case OP_##OPCODE:                                                     \
    disasm_##opcode(r, l);                                              \
    break
#define operator(OPCODE)                                                \
  case OP_##OPCODE:                                                     \
    disasm_operator(r, l, OP_##OPCODE);                                 \
    break
void disasm(lambda_t* l){
    line_t *r = line_init();
    
    while(r->is_run){
        switch(get_code){
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
        check_next_line(r, l);
    }
    line_puts(r);
}

#undef operator
#undef map