
#include <stdio.h>
#include "lib/lambda.h"
#include "com/ast.h"
#include "SLang.h"

extern FILE * yyin;
extern int yyparse (ast_t **modlue);

ast_t* front_process(char *slang_file){
    FILE * in = fopen(slang_file, "r");
    yyin = in;
    ast_t * module;
    module = NULL;
    yyparse(&module);
    fclose(in);
    return module;
}

void back_process(ast_t* module, char * scom_file){
    FILE * out = fopen(scom_file, "w");
    lambda_t *lambda = lambda_init();
    compile_stmts(module, lambda);
    save_scom(lambda, out);
    fclose(out);
}

void compile_file(char *slang_file, char *scom_file){   
    ast_t * module = front_process(slang_file);
    back_process(module, scom_file);
}