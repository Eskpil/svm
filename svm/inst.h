#ifndef INST_H_
#define INST_H_

#include "./word.h"

typedef enum {

    INST_ICONST,
    INST_FCONST,
    INST_UCONST,

    // stack maniuplation
    INST_SWAP,
    INST_POP,
    INST_DUP,

    // math operatinons
    INST_IADD, // int 64 
    INST_ISUB, // int 64 
    INST_IDIV, // int 64 
    INST_IMUL, // int 64 
    INST_IMOD, // int 64
    
    INST_FADD, // float 64
    INST_FSUB, // float 64
    INST_FDIV, // float 64
    INST_FMUL, // float 64
    
    INST_UADD, // uint 64
    INST_USUB, // uint 64
    INST_UDIV, // uint 64
    INST_UMUL, // uint 64
    INST_UMOD, // unit 64

    // if logic equailty etc
    INST_BRNZ, // Branch if not zero
    INST_BRIZ,
    INST_JMP, // Jump
    INST_HALT, // Halt
    
    INST_IEQ, // Equals i64
    INST_IGT,  // Greather than i64

    INST_FEQ, // Equals f64
    INST_FGT,  // Greather than f64

    INST_UEQ, // Equals u64
    INST_UGT,  // Greather than u64
} Inst_Type;

typedef struct {
    Inst_Type type;
    Word operand;
} Inst;

const char *inst_type_as_cstr(Inst_Type type);

#endif 
