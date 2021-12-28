#include "./inst.h"
#include <stdlib.h>

const char *inst_type_as_cstr(Inst_Type inst) {
    switch (inst) {
        case INST_ICONST:
            return "inst_iconst";
        case INST_FCONST:
            return "inst_fconst";
        case INST_UCONST:
            return "inst_uconst";
        case INST_SWAP:
            return "inst_swap";
        case INST_POP:
            return "inst_pop";
        case INST_DUP: 
            return "inst_dup";

        case INST_IADD: 
            return "inst_iadd";
        case INST_ISUB:
            return "inst_isub";
        case INST_IDIV:
            return "inst_idiv";
        case INST_IMUL:
            return "inst_imul";
        case INST_IMOD:
            return "inst_imod";
            
        case INST_FADD: 
            return "inst_fadd";
        case INST_FSUB:
            return "inst_fsub";
        case INST_FDIV:
            return "inst_fdiv";
        case INST_FMUL:
            return "inst_fmul";
            
        case INST_UADD: 
            return "inst_uadd";
        case INST_USUB:
            return "inst_usub";
        case INST_UDIV:
            return "inst_udiv";
        case INST_UMUL:
            return "inst_umul";
        case INST_UMOD:
            return "inst_umod";

        case INST_BRNZ:
            return "inst_brnz";
        case INST_BRIZ:
            return "inst_briz";
        case INST_JMP:
            return "inst_jmp";
        case INST_HALT: 
            return "inst_halt";
            
        case INST_IEQ:
            return "inst_ieq";
        case INST_IGT:
            return "inst_igt";

        case INST_FEQ:
            return "inst_feq";
        case INST_FGT:
            return "inst_fgt";
            
        case INST_UEQ:
            return "inst_ueq";
        case INST_UGT:
            return "inst_ugt";

        default: 
            return "invalid_inst";
    }
}


