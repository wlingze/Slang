
#ifndef COM_LAMBDA_H
#define COM_LAMBDA_H
#include "lib/vector.h"
#include "file/scom.h"

typedef struct lambda{
    char *name;
    vector_template(char, code);
    vector_template(consts_t*, consts);
} lambda_t;

lambda_t * lambda_init();
void  lambda_emit_insn(lambda_t *this, char * fmt, ...);
#define emit_insn(...) lambda_emit_insn(lambda, __VA_ARGS__)

#endif