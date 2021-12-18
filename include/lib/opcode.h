
#ifndef LIB_OPCODE_H
#define LIB_OPCODE_H

enum {
    OP_STORE, 
    OP_LOAD_NUMBER, 
    OP_LOAD_STRING, 
    OP_LOAD_WORD, 

    OP_CALL, 
    OP_JZ, 
    OP_JMP,

    OP_ADD, 
    OP_SUB,
    OP_DIV, 
    OP_MUL, 

    OP_GRAETER, 
    OP_EQUAL
};

enum{
    J_FORWORD, 
    J_BACK
};


#endif 