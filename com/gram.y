%{
#define YYSTYPE char*
#include <stdio.h>
extern int yylex (void);
void yyerror(const char*);
%}

%token GIFT REINDEER DELIVERING  
%token WORD NEW_LINE OPERATOR EQUAL

%%
proprame    :   stmts   
            ;
stmts   :   stmt 
        |   stmts stmt 
        ;
stmt    :   call_expr 
        |   var_expr NEW_LINE
        ;
    
call_expr   :   REINDEER WORD DELIVERING GIFT expr NEW_LINE {printf("Santa Claus's reindeer [%s]\n", $2);}
            ;


var_expr    : GIFT expr  
            ;

expr    :   WORD EQUAL expr    {printf("Send a gift to [%s]\n", $1);}
        |   expr OPERATOR expr {printf("Adjusting the order of gift discharge [%s]\n", $2);}
        |   WORD                {printf("Storage of gifts [%s]\n",$1);}
        ;

%%
