%{
#include "com/ast.h"
#define YYSTYPE ast_t *
#include <stdio.h>
extern int yylex (void);
void yyerror(ast_t **modlue, const char*);
%}

%parse-param { ast_t **module}

%token GIFT REINDEER DELIVERING BACK STRING
%token WORD NEW_LINE NUMBER OPERATOR
%token AGAIN IF WANT ENDWANT NEXT 


%%
proprame    :   stmts   
                {$$ = *module = $1;}
            ;
stmts   :   stmt 
                {$$ = ast_init(AST_STMT, 1, $1);}
        |   stmts stmt
                {$$ = ast_add_child($1, $2);}
        ;
stmt    :   call_expr 
        |   want_stmt
        |   var_expr NEW_LINE
                {$$ = $1;} 
        ;

want_stmt :     WANT WORD lists ENDWANT  
                {$$ = ast_init(AST_WANT, 2, $2, $3);}
        ;

lists    :  list 
                {$$ = ast_init(AST_LISTS, 1, $1);}
        |  lists list 
                {$$ = ast_add_child($1, $2);}
        ;

list    :  IF OPERATOR expr NEXT stmts
                {$$ = ast_init(AST_LIST, 3, $2, $3, $5);}
        | list AGAIN 
                {$$ = ast_add_child($1, $2);}

call_expr   : call_expr BACK WORD NEW_LINE 
                {$$ = ast_add_child($1, $3);}
            | call_expr NEW_LINE 
                {$$ = $1;}
            | REINDEER WORD DELIVERING WORD WORD WORD  
                {$$ = ast_init(AST_FUNCTION, 4, $2, $4, $5, $6);}
            ;

var_expr    : GIFT expr  
                {$$=$2;}
            ;

expr    :   expr OPERATOR expr    
                {$$=ast_init(AST_EXPR, 3, $1, $2, $3);}
        |   WORD               
                {$$=$1;}
        |   NUMBER             
                {$$=$1;}
        |   STRING 
                {$$=$1;}
        ;



%%
