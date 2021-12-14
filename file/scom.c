
#include "file/scom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lambda_t *parse_scom_file(FILE *file);

lambda_t *load_scom_file(char *filename){
    FILE *file = fopen(filename, "r");
    lambda_t *main;
    if (!file){
        fprintf(stderr, "open file:[%s] error\n", filename);
        exit(-1);
    }
    if ((main = parse_scom_file(file)) == NULL){
        fprintf(stderr, "parse file:[%s] error", filename);
        exit(-1);
    }
    fclose(file);
    return main;
}

lambda_t * parse_scom_file(FILE *file){
    char magic[8];
    int code_len, const_array_len;

    if (fread(magic, 1, 8, file) != 8)
        return NULL;
    if(strncmp(magic, SCOM_FILE_MAGIC, 8))
        return NULL;
    
    if(fread(&code_len, 1, 4, file) != 4)
        return NULL;

    if(fread(&const_array_len, 1, 4, file) != 4)
        return NULL;

    
    lambda_t *main_lambda = malloc(sizeof(lambda_t));

    main_lambda->name = strdup("__main__");


    char * code = malloc(code_len);

    if(fread(code, 1, code_len, file) != code_len)
        return NULL;

    main_lambda->code = code;

    for (int i=0; i<const_array_len; i++){
        int len;
        consts_t *con = malloc(sizeof(consts_t));
        if(fread(&(con->const_type), 1, 4, file) != 4)
            goto faild;
        if(fread(&len, 1, 4, file) != 4)
            goto faild;
        
        con->const_ptr = malloc(len);
        if(fread(con->const_ptr, 1, len, file) != len)
            goto faild;
        vector_push(&(main_lambda->consts), con);
    }
    return main_lambda;
faild:
    free(main_lambda);
    return NULL;
}