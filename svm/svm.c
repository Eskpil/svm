#include "./svm.h"

const char *trap_as_cstr(Trap trap) {
    switch (trap) {
        case NO_TRAP:
           return "no_trap";
        case TRAP_STACK_UNDERFLOW:
           return "trap_stack_underflow"; 
        case TRAP_STACK_OVERFLOW:
           return "trap_stack_overflow";
        case TRAP_DIV_ZERO:
           return "trap_div_zero";
        default:
           return "unreachable_trap";
           exit(1);
    };
}
void svm_dump(FILE *stream, const Svm *svm) {
    fprintf(stream, "Stack:\n");
    if (svm->stack_size > 0) {
        for (size_t i = 0; i < svm->stack_size; ++i) {
            fprintf(stream, "  u64: %" PRIu64 ", i64: %" PRId64 ", f64: %lf, ptr: %p\n",
                    svm->stack[i].as_u64,
                    svm->stack[i].as_i64,
                    svm->stack[i].as_f64,
                    svm->stack[i].as_ptr);
        }
    } else {
        fprintf(stream, "  [empty]\n");
    }
}


void svm_execute_program(Svm *svm, int limit)   {
    while (limit != 0 && !svm->halted)  {
        Trap trap = svm_execute_inst(svm);
        if (trap != NO_TRAP) {
            fprintf(stderr, "Error: %s\n", trap_as_cstr(trap));
            exit(1);
        };

        if (limit > 0) {
            limit--;
        };
    }    
}

Trap svm_execute_inst(Svm *svm)  {
    if (svm->stack_size >= STACK_CAP)   {
        return TRAP_STACK_OVERFLOW; 
    }; 
    
    Inst inst = svm->program[svm->ip];

    switch (inst.type)  {
        case INST_ICONST: {
            svm->stack[svm->stack_size++].as_i64 = inst.operand.as_i64;                  
            svm->ip += 1;
        } break;
        case INST_FCONST: {
            svm->stack[svm->stack_size++].as_f64 = inst.operand.as_f64;                  
            svm->ip += 1;
        } break;
        case INST_UCONST: {
            svm->stack[svm->stack_size++].as_u64 = inst.operand.as_u64;                  
            svm->ip += 1;
        } break;                 
        case INST_SWAP: {
            if (svm->stack_size < inst.operand.as_u64) {
                return TRAP_STACK_UNDERFLOW;
            };

            const uint64_t a = svm->stack_size - 1;
            const uint64_t b = svm->stack_size - (1 + inst.operand.as_u64);

            Word t = svm->stack[a];
            svm->stack[a] = svm->stack[a];
            svm->stack[b] = t;

            svm->ip += 1;
        } break;
        case INST_POP: {
            if (svm->stack_size < 1) {
                return TRAP_STACK_UNDERFLOW;
            };
            svm->stack_size -= 1;         
            svm->ip += 1;
        } break;
        case INST_DUP: {
           if (svm->stack_size < 1) {
                return TRAP_STACK_UNDERFLOW; 
           };     

           svm->stack[svm->stack_size] = svm->stack[svm->stack_size - 1 - inst.operand.as_u64];
           svm->stack_size += 1;
           svm->ip += 1;
        } break;

        case INST_IADD: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }
            
            svm->stack[svm->stack_size - 2].as_i64 += svm->stack[svm->stack_size - 1].as_i64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_ISUB: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            } 

            svm->stack[svm->stack_size - 2].as_i64 -= svm->stack[svm->stack_size - 1].as_i64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_IMUL: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_i64 *= svm->stack[svm->stack_size - 1].as_i64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_IDIV: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_i64 /= svm->stack[svm->stack_size - 1].as_i64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_IMOD: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }           

            svm->stack[svm->stack_size - 2].as_i64 %= svm->stack[svm->stack_size - 1].as_i64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_FADD: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }
            
            svm->stack[svm->stack_size - 2].as_f64 += svm->stack[svm->stack_size - 1].as_f64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_FSUB: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            } 

            svm->stack[svm->stack_size - 2].as_f64 -= svm->stack[svm->stack_size - 1].as_f64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_FMUL: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_f64 *= svm->stack[svm->stack_size - 1].as_f64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_FDIV: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_f64 /= svm->stack[svm->stack_size - 1].as_f64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_UADD: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }
            
            svm->stack[svm->stack_size - 2].as_u64 += svm->stack[svm->stack_size - 1].as_u64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_USUB: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            } 

            svm->stack[svm->stack_size - 2].as_u64 -= svm->stack[svm->stack_size - 1].as_u64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_UMUL: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_u64 *= svm->stack[svm->stack_size - 1].as_u64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_UDIV: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_u64 /= svm->stack[svm->stack_size - 1].as_u64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_UMOD: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }           

            svm->stack[svm->stack_size - 2].as_u64 %= svm->stack[svm->stack_size - 1].as_u64;
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;


        case INST_JMP: {
            svm->ip = inst.operand.as_u64; 
        } break;
        case INST_HALT: {
            svm->halted = true;        
        } break;
        case INST_BRNZ: {
            if (svm->stack_size < 1) {
                return TRAP_STACK_UNDERFLOW;
            };              

            if (svm->stack[svm->stack_size - 1].as_u64 != 0) {
                svm->ip = inst.operand.as_u64;
            } else {
                svm->ip += 1; 
            };

            svm->stack_size -= 1;
        } break;
        case INST_BRIZ: {
            if (svm->stack_size < 1) {
                return TRAP_STACK_UNDERFLOW;
            };
            
            if (svm->stack[svm->stack_size - 1].as_u64 == 0) {
                svm->ip = inst.operand.as_u64;
            } else {
                svm->ip += 1;
            }
        } break;

        case INST_IEQ: {
            if (svm->stack_size < 2) {
               return TRAP_STACK_UNDERFLOW;
            };              

            svm->stack[svm->stack_size - 2].as_u64 = svm->stack[svm->stack_size - 1].as_i64 == svm->stack[svm->stack_size - 2].as_i64;

            svm->ip++;
            svm->stack_size -= 1;
        } break;
        case INST_IGT: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_u64 = svm->stack[svm->stack_size - 1].as_i64 >= svm->stack[svm->stack_size - 2].as_i64;
            svm->ip += 1;
            svm->stack_size -= 1;
        } break;

        case INST_FEQ: {
            if (svm->stack_size < 2) {
               return TRAP_STACK_UNDERFLOW;
            };              

            svm->stack[svm->stack_size - 2].as_u64 = svm->stack[svm->stack_size - 1].as_f64 == svm->stack[svm->stack_size - 2].as_f64;

            svm->ip++;
            svm->stack_size -= 1;
        } break;
       
        case INST_FGT: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_u64 = svm->stack[svm->stack_size - 1].as_f64 >= svm->stack[svm->stack_size - 2].as_f64;
            svm->ip += 1;
            svm->stack_size -= 1;
        } break;
       
        case INST_UEQ: {
            if (svm->stack_size < 2) {
               return TRAP_STACK_UNDERFLOW;
            };              

            svm->stack[svm->stack_size - 2].as_u64 = svm->stack[svm->stack_size - 1].as_u64 == svm->stack[svm->stack_size - 2].as_u64;

            svm->ip++;
            svm->stack_size -= 1;
        } break;
        case INST_UGT: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size - 2].as_u64 = svm->stack[svm->stack_size - 1].as_u64 >= svm->stack[svm->stack_size - 2].as_u64;
            svm->ip += 1;
            svm->stack_size -= 1;
        } break;

        case SYSCALL1: {
            assert(0 && "syscall1 is not implemented");
        } break;
        case SYSCALL2: {
            assert(0 && "syscall2 is not implemented");
        } break;        
        case SYSCALL3: {
            assert(0 && "syscall3 is not implemented");
        } break;  
        case SYSCALL4: {
            assert(0 && "syscall4 is not implemented");
        } break;
        case SYSCALL5: {   
            assert(0 && "syscall5 is not implemented");
        } break;        
        case SYSCALL6: {  
            assert(0 && "syscall6 is not implemented");
        } break; 
    };

    return NO_TRAP;
}

