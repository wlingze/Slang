#include "com/ast.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>


#define pthis ast_t* this
ast_t* ast_add_child(pthis, ast_t* child){
    vector_push_back(&(this->child), child);
    return this;
}

ast_t *ast_get_child(pthis, int index ){
    return vector_get(this->child, index);
}

int ast_get_child_count(pthis){
    return this->child.count;
}

ast_t* ast_to(pthis, int type){
    this->type = type;
    return this;
}

#undef pthis

ast_t* ast_init_type(int type){
    ast_t *ast = malloc(sizeof(ast_t));
    ast->type = type;
    vector_init(&(ast->child));
    return ast;
}

ast_t * ast_init(int type, int count, ...){

    ast_t * this = ast_init_type(type);
    va_list ap;
    va_start(ap, count);
    while (count--) {
        ast_t *child = va_arg(ap, ast_t*);
        ast_add_child(this, child);
    }
    va_end(ap);
    return this;
}


ast_t * ast_number_init(char* number){
    ast_t * ast = ast_init_type(AST_NUMBER);
    ast->int_value = atoi(number);
    return ast;
}

ast_t * ast_word_init(char *word){
    ast_t * ast = ast_init_type(AST_WORD);
    ast->string_value = strdup(word);
    return ast;
}

ast_t * ast_operator_init(char operator){
    ast_t * ast = ast_init_type(AST_OPERATOR);
    ast->char_value = operator;
    return ast;
}

ast_t * ast_string_init(char *str){
    ast_t * ast = ast_init_type(AST_STRING);
    str ++;
    str[strlen(str)-1] = 0;
    ast->string_value = strdup(str);
    return ast;
}