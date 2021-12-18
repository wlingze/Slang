%{
#include "com/ast.h"
#define YYSTYPE ast_t *
#include <stdio.h>
#include "parser.h"
int line = 1;
%}
%option noyywrap

%%
";"             {return NEW_LINE;}
":"             {return NEXT;}
"is"            {yylval=ast_operator_init('=');return OPERATOR;}
"gift"          {return GIFT;}
"reindeer"      {return REINDEER;}
"equal to"      {yylval=ast_operator_init('?'); return OPERATOR;}
"greater than"  {yylval=ast_operator_init('>'); return OPERATOR;}
"if the gift"   {return IF;}
"delivering gift"    {return DELIVERING;}
"brings back gift"   {return BACK;}
"this family wants gift"                {return WANT;}
"ok, they should already have a gift;"  {return ENDWANT;}
"Brave reindeer! Fear no difficulties!" {yylval=ast_init_type(AST_AGAIN);return AGAIN;}

<<EOF>>         {return 0;}

[ ]             {/* empty */}
[\n]            {line++;}
[-+*/]          {yylval=ast_operator_init(yytext[0]); return OPERATOR;}
[a-zA-Z]+       {yylval=ast_word_init(yytext); return WORD;}
[0-9]+          {yylval=ast_number_init(yytext); return NUMBER;}
\"([^\"]*)\"    {yylval=ast_string_init(yytext); return STRING;}
(#[^#]*#)       {/* empty */}
%%

void yyerror(ast_t **modlue,const char *msg) {
    printf("\nError at %d: %s\n\t%s\n", line, yytext, msg);
    exit(1);
}
