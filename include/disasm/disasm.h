
#ifndef DISASM_DISASM_H
#define DISASM_DISASM_H

#include "lib/lambda.h"
#include "disasm/line.h"

void disasm(lambda_t* lambda);

#define output(addr, fmt, ...) \
    line_fmt(r, addr, fmt, ##__VA_ARGS__)

#endif 