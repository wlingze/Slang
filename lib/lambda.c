
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib/lambda.h"
#include "lib/opcode.h"
#include "com/ast.h"
#include <assert.h>

#define pthis lambda_t *this

lambda_t * lambda_init(){
    lambda_t * lambda = malloc(sizeof(lambda_t));
    vector_init(&(lambda->code));
    vector_init(&(lambda->number));
    vector_init(&(lambda->string));
    vector_init(&(lambda->word));
    return lambda;
}

char lambda_get_code(pthis, int idx){
    return vector_get(this->code, idx);
}

int lambda_get_number(pthis, int idx){
    return vector_get(this->number, idx);
}

char* lambda_get_string(pthis, int idx){
    return vector_get(this->string, idx);
}

char* lambda_get_word(pthis, int idx){
    return vector_get(this->word, idx);
}

int lambda_get_code_count(pthis){
    return this->code.count;
}

int lambda_set_code(pthis, int idx, char code){
    vector_set(&(this->code), idx, code);
}

int lambda_set_string(pthis, char * str){
    
    int i = 0;
    char *item;
    vector_each(this->string, i, item){
        if (!strcmp(item, str))
            return i;
    }

    vector_push_back(&(this->string), str);
    return this->string.count-1;
}

int lambda_set_word(pthis, char * word){
    
    int i = 0;
    char *item;
    vector_each(this->word, i, item){
        if (!strcmp(item, word))
            return i;
    }

    vector_push_back(&(this->word), word);
    return this->word.count-1;
}

int lambda_set_number(pthis, int num){
    
    int i = 0;
    int item;
    vector_each(this->number, i, item){
        if (item == num)
            return i;
    }

    vector_push_back(&(this->number), num);
    return this->number.count-1;
}


void lambda_insn(pthis, char opcode){
    vector_push_back(&(this->code), opcode);
}

void emit_insn_call(pthis, ast_t *ast){
    insn(OP_CALL)
    insn(lambda_set_word(this, ast->string_value));
}

#define map(operator, OPCODE)                                                 \
    case operator:\
        insn(OPCODE);               \
        break
void emit_insn_operator(pthis, ast_t *ast){
    switch(ast->char_value){
        map('+', OP_ADD);
        map('-', OP_SUB);
        map('*', OP_MUL);
        map('/', OP_DIV);
        map('>', OP_GRAETER);
        map('?', OP_EQUAL);
    }
}
#undef map

void emit_insn_store(pthis, ast_t *ast){
    insn(OP_STORE);
    insn(lambda_set_word(this, ast->string_value));
}

void emit_insn_load_word(pthis, ast_t *ast){
    insn(OP_LOAD_WORD);
    insn(lambda_set_word(this, ast->string_value));
}


void emit_insn_load_number(pthis, ast_t *ast){
    insn(OP_LOAD_NUMBER);
    insn(lambda_set_number(this, ast->int_value));
}


void emit_insn_load_string(pthis, ast_t *ast){
    insn(OP_LOAD_STRING);
    insn(lambda_set_string(this, ast->string_value));
}

#define map(OPCODE, opcode)                                                 \
    case OP_##OPCODE:                                                         \
        emit_insn_##opcode(this, ast);                                       \
        break
void  lambda_emit_insn(pthis, int opcode, ast_t *ast){
    switch (opcode){
        map(STORE, store);
        map(LOAD_NUMBER, load_number);
        map(LOAD_WORD, load_word);
        map(LOAD_STRING, load_string);
    }

}
#undef map

void emit_insn_jz(pthis, int redirection, long offset){
    if (redirection == this->code.count){
        insn(OP_JZ);
        insn(J_FORWORD);
        insn((offset >> 8) & 0xff);
        insn(offset & 0xff);
    } else {
        redirection ++;
        if (offset < 0){
            offset = -offset;
            lambda_set_code(this, redirection++, J_BACK);
        } else {
            redirection ++;
        }
        lambda_set_code(this, redirection++, (offset >> 8) & 0xff);
        lambda_set_code(this, redirection++, offset & 0xff);
    }
}

void emit_insn_jmp(pthis, int target){
    int offset = target - (lambda_get_code_count(this) + 4);
    insn(OP_JMP);
    if (offset < 0){
        offset = -offset;
        insn(J_BACK);
    } else {
        insn(J_FORWORD);
    }
    insn((offset >> 8) & 0xff);
    insn(offset & 0xff);
}

#undef pthis