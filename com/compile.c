
#include <stddef.h>
#include "com/ast.h"
#include "lib/lambda.h"
#include "lib/opcode.h"
#include "lib/vector.h"
#include "com/com_want.h"

#define arg ast_t *ast, lambda_t* lambda

void compile_number(arg){
    emit_insn(OP_LOAD_NUMBER, ast);
}

void compile_string(arg){
    emit_insn(OP_LOAD_STRING, ast);
}

void compile_word_push(arg){
    emit_insn(OP_LOAD_WORD, ast);
}

void compile_word_pop(arg){
    emit_insn(OP_STORE, ast);
}

void compile_function(arg){
    ast_t *func = ast_get_child(ast, 0);
    ast_t *arg1 = ast_get_child(ast, 1);
    ast_t *arg2 = ast_get_child(ast, 2);
    ast_t *arg3 = ast_get_child(ast, 3);

    emit_insn(OP_LOAD_WORD, arg1);
    emit_insn(OP_LOAD_WORD, arg2);
    emit_insn(OP_LOAD_WORD, arg3);

    emit_insn_call(lambda, func);

    if (ast_get_child_count(ast) == 5){
        ast_t *ret = ast_get_child(ast, 4);
        if (ret->type == AST_WORD)
            emit_insn(OP_STORE, ret);
    }
    
}



#define map(var, TYPE, type)                                                 \
    case AST_##TYPE:                                                         \
        compile_##type((var), lambda);                                       \
        break
void compile_expr(arg){
    ast_t * left     = ast_get_child(ast, 0);
    ast_t * operator = ast_get_child(ast, 1);
    ast_t * right    = ast_get_child(ast, 2);

    if (operator->char_value == '='){
        switch(right->type){
            map(right, EXPR, expr);
            map(right, WORD, word_push);
            map(right, NUMBER, number);
            map(right, STRING, string);
        }
        compile_word_pop(left, lambda);
        return ;
    }

    switch(left->type){
        map(left, EXPR, expr);
        map(left, WORD, word_push);
        map(left, NUMBER, number);
    }

    switch(right->type){
        map(right, EXPR, expr);
        map(right, WORD, word_push);
        map(right, NUMBER, number);
        map(right, STRING, string);
    }

    emit_insn_operator(lambda, operator);
}

void compile_stmt(arg){
    switch(ast->type){
        map(ast, EXPR, expr);
        map(ast, FUNCTION, function);
        map(ast, WANT, want);
    }
    
}
#undef map

void compile_stmts(arg){

    int i = 0;
    ast_t*child = NULL;
    ast_each_child(ast, i, child)
        compile_stmt(child, lambda);
}


#undef arg
