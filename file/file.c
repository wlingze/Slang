
#include <stdio.h>
#include <stdlib.h>
#include "file/file.h"

file_t * file_init(char * filename){
    file_t *file = malloc(sizeof(file_t));

    file->filename = filename;
    FILE * f = fopen(filename, "r");
    if (!f){
        fprintf(stderr, "slang: can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    file->file = f;
    return file;
}