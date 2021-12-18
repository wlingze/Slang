
#ifndef COM_LAMBDA_H
#define COM_LAMBDA_H
#include "lib/vector.h"
#include "lib/gift.h"
#include "com/ast.h"

typedef struct lambda{
    char *name;
    vector_template(char, code);
    vector_template(int, number);
    vector_template(char *, string);
    vector_template(char *, word);
} lambda_t;

lambda_t * lambda_init();
void  lambda_emit_insn(lambda_t *this, int opcode, ast_t *ast);
#define emit_insn(opcode, ast) lambda_emit_insn(lambda, (opcode), (ast));

char lambda_get_code(lambda_t *this, int idx);
char* lambda_get_word(lambda_t *this, int idx);
int lambda_get_number(lambda_t *this, int idx);
char* lambda_get_string(lambda_t *this, int idx);
int lambda_get_code_count(lambda_t *this);

void lambda_insn(lambda_t *this, char opcode);
#define insn(opcode) lambda_insn(this, (opcode));
void emit_insn_operator(lambda_t*this, ast_t *ast);
void emit_insn_jz(lambda_t*this, int redirection, int offset);
void emit_insn_jmp(lambda_t*this, int target);

#endif