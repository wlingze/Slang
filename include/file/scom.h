
#ifndef FILE_SCOM_H
#define FILE_SCOM_H

#include "lib/vector.h"

typedef struct consts{
    int const_type;
    void * const_ptr;
} consts_t;

typedef struct lambda{
    char *name;
    char *code;
    vector_template(consts_t, consts);
} lambda_t;


lambda_t *load_scom_file(char *filename);

#define SCOM_FILE_MAGIC "SCOMFILE"


#endif