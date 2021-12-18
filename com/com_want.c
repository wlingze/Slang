#include "com/ast.h"
#include "lib/lambda.h"
#include "com/compile.h"

#define arg ast_t *ast, lambda_t *lambda, ast_t* word, int start
#define map(TYPE, type)                                                 \
    case AST_##TYPE:                                                         \
        compile_##type(expr, lambda);                                       \
        break
void compile_list(arg){
    ast_t * operator = ast_get_child(ast, 0);
    ast_t * expr = ast_get_child(ast, 1);
    ast_t * stmts = ast_get_child(ast, 2);

    compile_word_push(word, lambda);
    switch(expr->type){
        map(EXPR, expr);
        map(WORD, word_push);
        map(NUMBER, number);
    }

    emit_insn_operator(lambda, operator);

    int redirection = lambda_get_code_count(lambda);
    emit_insn_jz(lambda, redirection, 0xffff);

    compile_stmts(stmts, lambda);

    int offset = lambda_get_code_count(lambda) - redirection;
    emit_insn_jz(lambda, redirection, offset);

    if (ast_get_child_count(ast) == 4)
        if(ast_get_child(ast, 3)->type == AST_AGAIN)
            emit_insn_jmp(lambda, start);
}
#undef map
#undef arg

void compile_want(ast_t *ast, lambda_t *lambda){
    ast_t *word = ast_get_child(ast, 0);
    ast_t *lists = ast_get_child(ast, 1);
    ast_t *list;
    int i = 0;
    int start = lambda_get_code_count(lambda);
    ast_each_child(lists, i, list)
        compile_list(list, lambda, word, start);
}
