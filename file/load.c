#include "file/scom.h"
#include "com/com.h"
#include "lib/lambda.h"
#include "vm/vm_call.h"
#include "SLang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void invalid_suffix(){
    fprintf(stderr, "suffix must be .scom or .slang\n");
    exit(-1);
}

int check_suffix(char *path, char *dir, char *name){
    char * suffix = rindex(path, '.');

    if(suffix == NULL)
        invalid_suffix();


    char * slash = rindex(path, '/');
    if(slash == NULL){
        strcpy(dir, ".");
        memcpy(name, path, suffix-path);
        name[suffix-path] = 0;
    } else {
        memcpy(dir, path, slash-path);
        dir[slash-path] = 0;

        memcpy(name, slash+1, suffix - (slash+1));
        name[suffix-(slash+1)] = 0;
    }
    
    if (!strcmp(suffix, ".scom"))
        return 0;
    
    if (!strcmp(suffix, ".slang"))
        return 1;

    invalid_suffix();
}

void load_file(char *path){
    char dir[0x60];
    char name[0x60];
    char slang_file[0x120];
    char scom_file[0x120];

    int is_slang = check_suffix(path, dir, name);

    sprintf(slang_file, "%s/%s.slang", dir, name);
    sprintf(scom_file, "%s/%s.scom", dir, name);

    if (FLAG == COMPILE){
        compile_file(slang_file, scom_file);
    } else if (FLAG == RUN){
        if (is_slang)
            compile_file(slang_file, scom_file);
        lambda_t *lambda = load_scom(scom_file);
        vm_call_lambda(lambda);
    }
}