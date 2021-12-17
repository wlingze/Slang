
#ifndef FILE_SCOM_H
#define FILE_SCOM_H 
#include "lib/lambda.h"
#include <stdio.h>

#define SCOM_MAGIC  "SCOM_LZ\x00"

void save_scom(lambda_t *lambda, FILE *out);
lambda_t* load_scom(char *filename);

#endif 
