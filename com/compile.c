
#include <stddef.h>
#include "com/ast.h"
#include "com/lambda.h"
#include "lib/vector.h"


void compile_number(ast_t * ast, lambda_t *lambda){
    emit_insn("push %d\n", ast->int_value);
}

void compile_word_push(ast_t * ast, lambda_t *lambda){
    emit_insn("push %s\n", ast->string_value);
}

void compile_word_pop(ast_t * ast, lambda_t *lambda){
    emit_insn("pop %s\n", ast->string_value);
}

void compile_function(ast_t *ast, lambda_t *lambda){
    ast_t *func = ast_get_child(ast, 0);
    ast_t *arg1 = ast_get_child(ast, 1);
    ast_t *arg2 = ast_get_child(ast, 2);
    ast_t *arg3 = ast_get_child(ast, 3);
    ast_t * ret = ast_get_child(ast, 4);

    emit_insn("push %s\n", arg1->string_value);
    emit_insn("push %s\n", arg2->string_value);
    emit_insn("push %s\n", arg3->string_value);
    emit_insn("call %s\n", func->string_value);

    if (ret){
        emit_insn("pop %s\n", ret->string_value);
    }
}


#define map(var, TYPE, type)                                                 \
    case AST_##TYPE:                                                         \
        compile_##type((var), lambda);                                       \
        break
void compile_expr(ast_t * ast, lambda_t * lambda){
    ast_t * left     = ast_get_child(ast, 0);
    ast_t * operator = ast_get_child(ast, 1);
    ast_t * right    = ast_get_child(ast, 2);


    switch(right->type){
        map(right, EXPR, expr);
        map(right, WORD, word_push);
        map(right, NUMBER, number);
    }

    if (operator->char_value == '='){
        compile_word_pop(left, lambda);
        return ;
    }

    switch(left->type){
        map(left, EXPR, expr);
        map(left, WORD, word_push);
        map(left, NUMBER, number);
    }
    emit_insn("%c\n", operator->char_value);
}

void compile_stmt(ast_t * ast, lambda_t *lambda){
    switch(ast->type){
        map(ast, EXPR, expr);
        map(ast, FUNCTION, function);
    }
    
}
#undef map

void compile_stmts(ast_t * ast, lambda_t * lambda){

    int i = 0;
    ast_t*child = NULL;
    ast_each_child(ast, i, child)
        compile_stmt(child, lambda);
}


