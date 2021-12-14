
#include "file/scom.h"


void vm_call_lambda(lambda_t *lambda){
    int ip = 0;
    char * code = lambda->code;
    vector_t *v_const = &(lambda->consts);

    while(1){
        switch(code[ip]){
            #include "vm/runtime/display.h"
        }
    }
}