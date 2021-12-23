
#include <stdio.h>
#include <stdlib.h>
#include "lib/lambda.h"
#include "com/ast.h"
#include "SLang.h"

extern FILE * yyin;
extern FILE * yyout;
extern int yyparse (ast_t **modlue);

ast_t* front_process(char *slang_file){
    yyin = fopen(slang_file, "r");
    if (!yyin){
        printf("don't open file %s", slang_file);
        exit(EXIT_FAILURE);
    }
    yyout = fopen("/dev/null", "w");
    ast_t * m = NULL;
    yyparse(&m);
    fclose(yyin);
    fclose(yyout);
    return m;
}

void back_process(ast_t* m, char * scom_file){
    FILE * out = fopen(scom_file, "w");
    lambda_t *l = lambda_init();
    compile_stmts(m, l);
    save_scom(l, out);
    fclose(out);
}

void compile_file(char *slang_file, char *scom_file){   
    ast_t * module = front_process(slang_file);
    back_process(module, scom_file);
}