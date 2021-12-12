#include "./inst.h"
#include <stdlib.h>

const char *inst_type_as_cstr(Inst_Type inst) {
    switch (inst) {
        case INST_PUSH: 
            return "inst_push";
        case INST_SWAP:
            return "inst_swap";
        case INST_POP:
            return "inst_pop";
        case INST_DUP: 
            return "inst_dup";

        case INST_ADDI: 
            return "inst_addi";
        case INST_SUBI:
            return "inst_subi";
        case INST_DIVI:
            return "inst_divi";
        case INST_MULI:
            return "inst_muli";
        case INST_MODI:
            return "inst_modi";
            
        case INST_ADDF: 
            return "inst_addf";
        case INST_SUBF:
            return "inst_subf";
        case INST_DIVF:
            return "inst_divf";
        case INST_MULF:
            return "inst_mulf";
            
        case INST_ADDU: 
            return "inst_addu";
        case INST_SUBU:
            return "inst_subu";
        case INST_DIVU:
            return "inst_divu";
        case INST_MULU:
            return "inst_mulu";
        case INST_MODU:
            return "inst_modu";

        case INST_BRNZ:
            return "inst_brnz";
        case INST_JMP:
            return "inst_jmp";
        case INST_HALT: 
            return "inst_halt";
            
        case INST_EQI:
            return "inst_eqi";
        case INST_NQI:
            return "inst_nqi";
        case INST_GTI:
            return "inst_gti";
        case INST_LTI:
            return "inst_lti";

        case INST_EQF:
            return "inst_eqf";
        case INST_NQF:
            return "inst_nqf";
        case INST_GTF:
            return "inst_gtf";
        case INST_LTF:
            return "inst_ltf";
            
        case INST_EQU:
            return "inst_equ";
        case INST_NQU:
            return "inst_nqu";
        case INST_GTU:
            return "inst_gtu";
        case INST_LTU:
            return "inst_ltu"; 

        default: 
            return "invalid_inst";
    }
}


