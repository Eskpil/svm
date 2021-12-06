#ifndef INST_H_
#define INST_H_

#include "./word.h"

typedef enum {
    // stack maniuplation
    INST_PUSH,
    INST_SWAP,
    INST_POP,
    INST_DUP,

    // math operatinons
    INST_ADDI, // int 64 
    INST_SUBI, // int 64 
    INST_DIVI, // int 64 
    INST_MULI, // int 64 
    INST_MODI, // int 64
    
    INST_ADDF, // float 64
    INST_SUBF, // float 64
    INST_DIVF, // float 64
    INST_MULF, // float 64
    
    INST_ADDU, // uint 64
    INST_SUBU, // uint 64
    INST_DIVU, // uint 64
    INST_MULU, // uint 64
    INST_MODU, // unit 64

    // if logic equailty etc
    INST_BRNZ, // Branch if not zero
    INST_JMP, // Jump
    INST_HALT, // Halt
    
    INST_EQI, // Equals i64
    INST_NQI, // Not equals i64

    INST_EQF, // Equals f64
    INST_NQF, // Not equals f64

    INST_EQU, // Equals u64
    INST_NQU, // Not equals u64

} Inst_Type;

typedef struct {
    Inst_Type type;
    Word operand;
} Inst;

const char *inst_type_as_cstr(Inst_Type type);

#endif 
