
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "com/lambda.h"

lambda_t * lambda_init(){
    lambda_t * lambda = malloc(sizeof(lambda_t));
    vector_init(&(lambda->code));
    vector_init(&(lambda->consts));
    return lambda;
}

void  lambda_emit_insn(lambda_t *this, char * fmt, ...){
    va_list ap;
    va_start(ap, fmt);  
    vprintf(fmt, ap);
    va_end(ap);

}