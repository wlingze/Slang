%{
#include "com/ast.h"
#define YYSTYPE ast_t *
#include <stdio.h>
#include "parser.h"
int line = 1;
%}
%option noyywrap

%%
"gift"               {return GIFT;}
"reindeer"           {return REINDEER;}
"delivering gift"    {return DELIVERING;}
"brings back gift"   {return BACK;}
"is"                 {yylval=ast_operator_init('=');return EQUAL;}

<<EOF>>         {return 0;}

[ ]             {/* empty */}
[\n]            {line++;}
[-+*/]          {yylval=ast_operator_init(yytext[0]); return yytext[0];}
[a-zA-Z]+       {yylval=ast_word_init(yytext); return WORD;}
[0-9]+          {yylval=ast_number_init(yytext); return NUMBER;}
";"             {return NEW_LINE;}
%%

void yyerror(ast_t **modlue,const char *msg) {
    printf("\nError at %d: %s\n\t%s\n", line, yytext, msg);
    exit(1);
}
