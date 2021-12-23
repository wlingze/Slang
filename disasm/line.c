

#include "disasm/line.h"
#include "lib/vector.h"
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

line_t * line_init(){
    line_t *this = malloc(sizeof(line_t));
    this->rip = 0;
    this->is_run = 1;
    vector_init(&(this->asm_code));
    vector_init(&(this->jmp_addr));
    return this;
}

#define pthis line_t *this

void line_code(pthis, int addr, char * disasm_code){
    addr_t *a = malloc(sizeof(addr_t));
    a->addr = addr;
    a->disasm = strdup(disasm_code);
    vector_push_back(&(this->asm_code), a);
}

void line_jmp(pthis, int jmp_addr){
    vector_push_back(&(this->jmp_addr), jmp_addr);
}

void line_is_target(pthis, addr_t* item){
    int i=0, addr;
    vector_each(this->jmp_addr, i, addr){
        if(item->addr == addr)
            printf("\n");
    }
}

void line_puts(pthis){
    int i=0;
    addr_t *item;
    vector_each(this->asm_code, i, item){
        line_is_target(this, item);
        printf("%d\t%s", item->addr, item->disasm);
    }
}

void line_fmt(pthis,int addr, char *fmt, ...){
    va_list ap;
    char buffer[0x80];
    
    va_start(ap, fmt);
    // vsnprintf(buffer, 0x80, fmt, ap);
    vsprintf(buffer, fmt, ap);
    va_end(ap);
    line_code(this, addr, buffer);
}

#undef pthis
