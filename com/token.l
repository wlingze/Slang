%{
#define YYSTYPE char*
#include <stdio.h>
#include "gram.h"
int line = 1;
char *sym2operator(char sym);
%}
%option noyywrap

%%
"gift"          {return GIFT;}
"reindeer"      {return REINDEER;}
"delivering"    {return DELIVERING;}
<<EOF>>         {return 0;}
[ ]             {/* empty */}
[\n]            {line++;}
[-+*/]          {yylval=sym2operator(yytext[0]); return OPERATOR;}
[is]+           {return EQUAL;}
[a-zA-Z0-1]+    {yylval=strdup(yytext); return WORD;}
";"             {return NEW_LINE;}
%%

void yyerror(const char *msg) {
    printf("\nError at %d: %s\n\t%s\n", line, yytext, msg);
    exit(1);
}


char *sym2operator(char sym){
    switch(sym){
        case '+' :
            return strdup("add");
        case '-' :
            return strdup("sub ");
        case '*' :
            return strdup("mul");
        case '/' :
            return strdup("div");
    }
}