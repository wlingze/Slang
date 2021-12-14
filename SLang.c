#include "file/load.h"
#include "SLang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void help(){
    puts("Slang v0.01");
    puts("compile file:\t\t-c [filename.slang]");
    puts("decompile file:\t\t-d [filename.scom]");
    puts("run file\t\t-r [filename.scom/filename.slang]");
}

int main(int argc, char * argv[]){
    if (argc == 1){
        help();
    }

    char * sig = argv[1];
    if (sig == NULL){
        return 1;
    }
    if (!strcmp(sig, "-c")){
        FLAG = COMPILE;
    } else if (!strcmp(sig, "-d")){
        FLAG = DEASM;
    } else if (!strcmp(sig, "-g")){
        FLAG = DEBUG;
    } else if (!strcmp(sig, "-r")){
        FLAG = RUN;
    } else {
        help();
        return 0;
    }
    load_file(argv[2]);
    return 0;
}