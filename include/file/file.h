
#ifndef COM_FILE_H
#define COM_FILE_H

#include <stdio.h>

typedef struct file {
    FILE * file;
    char * filename;
} file_t;


file_t * file_init(char * filename);

#endif