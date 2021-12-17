
#ifndef COM_COMPILE_H
#define COM_COMPILE_H

#include "com/ast.h"
#include "lib/lambda.h"

void compile_stmts(ast_t * ast, lambda_t * lambda);
#endif