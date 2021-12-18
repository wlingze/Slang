
#ifndef COM_AST_H
#define COM_AST_H

#include "lib/vector.h"

enum{
    AST_NUMBER, 
    AST_WORD,
    AST_STRING,
    AST_IF_CAUSE, 
    AST_ELSE_CAUSE, 
    AST_FUNCTION , 
    AST_OPERATOR, 
    AST_EXPR , 
    AST_STMT, 
    AST_WANT, 
    AST_LISTS, 
    AST_LIST, 
    AST_AGAIN

};

typedef struct ast{
    int type; // ast node type
    union{
        char * string_value;
        int int_value;
        char char_value;
    };
    vector_template(struct ast*, child);
} ast_t;

#define ast_each_child(ast, i, item) \
    vector_each((ast)->child, i, (item))

ast_t * ast_init(int type, int count, ...);
ast_t* ast_init_type(int type);
ast_t* ast_add_child(ast_t * this, ast_t* child);
ast_t *ast_get_child(ast_t * this, int index );
int ast_get_child_count(ast_t * this);

ast_t * ast_number_init(char* number);
ast_t * ast_word_init(char *word);
ast_t * ast_operator_init(char operator);
ast_t * ast_string_init(char *str);

#endif 