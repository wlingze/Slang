#ifndef DISASM_LINE
#define DISASM_LINE 

#include "lib/vector.h"

typedef struct addr{
    int addr;
    char * disasm;
} addr_t;

typedef struct line {
    int rip;
    int is_run;
    vector_template(addr_t*,  asm_code);
    vector_template(int, jmp_addr);
} line_t;


line_t * line_init();
void line_fmt(line_t *this, int addr, char *fmt, ...);
void line_puts(line_t *this);
void line_jmp(line_t *this, int jmp_addr);
#endif