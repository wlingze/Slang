
#ifndef COM_COMPILE_H
#define COM_COMPILE_H

#include "com/ast.h"
#include "com/lambda.h"

void compile_stmts(ast_t * mod, lambda_t * lambda);

#endif