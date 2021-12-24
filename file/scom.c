
#include "com/ast.h"
#include "file/scom.h"
#include "lib/lambda.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define scom(p, size) fwrite((p), 1, (size), out);
void save_scom(lambda_t *lambda, FILE *out){
    int i=0;
    char *item;
    int len;

    scom(SCOM_MAGIC, 8);

    // code 
    scom(&(lambda->code.count), 4);
    scom(lambda->code.data, lambda->code.count);

    // number 
    scom(&(lambda->number.count), 4);
    scom(lambda->number.data, lambda->number.count * 4);

    // string 
    // word 
    scom(&(lambda->string.count), 4);
    scom(&(lambda->word.count), 4);

    vector_each(lambda->string, i, item){
        len = strlen(item);
        scom(&(len), 4);
        scom(item, len);
    }

    i = 0;
    vector_each(lambda->word, i, item){
        len = strlen(item);
        scom(&(len), 4);
        scom(item, len);
    }
}
#undef scom


#define scom(buf, size) fread((buf), 1, (size), in);
lambda_t* load_scom(char *filename){
    FILE *in = fopen(filename, "r");
    int i=0;
    int len;
    int string_count, word_count;
    char * item;

    lambda_t *lambda = lambda_init();

    char *magic;
    scom(magic, 8);
    if (strcmp(magic, SCOM_MAGIC)){
        printf("scom file magic error: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // code
    scom(&(lambda->code.count), 4);
    lambda->code.data = malloc(lambda->code.count);
    scom(lambda->code.data, lambda->code.count);

    // number 
    scom(&(lambda->number.count), 4);
    lambda->number.data = malloc(lambda->number.count * 4);
    scom(lambda->number.data, lambda->number.count * 4);

    // string 
    // word 
    scom(&(string_count), 4);
    scom(&(word_count), 4);

    for(i=0; i<string_count; i++){
        scom(&(len), 4);
        item = malloc(len);
        scom(item, len);
        item[len] = 0;
        vector_push_back(&(lambda->string), item);
    }

    for(i=0; i<word_count; i++){
        scom(&(len), 4);
        item = malloc(len);
        scom(item, len);
        item[len] = 0;
        vector_push_back(&(lambda->word), item);
    }

    return lambda;
}