#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_CAP 8192
#define PROGRAM_CAP 65565

typedef enum {
    NO_TRAP,
    TRAP_STACK_OVERFLOW,
    TRAP_STACK_UNDERFLOW,
    TRAP_DIV_ZERO,
} Trap;

typedef int64_t Word; 

typedef enum {
    // stack maniuplation
    INST_PUSH,
    INST_SWAP,
    INST_POP,
    INST_DUP,

    // math operatinons
    INST_ADD, 
    INST_SUB,
    INST_DIV,
    INST_MUL,

    // if logic equailty etc
    INST_BRNZ, // Branch if not zero
    INST_JMP, // Jump
    INST_HALT, // Halt
    INST_EQ, // Equals
    INST_NQ, // Not equals
} Inst_Type;

typedef struct {
    Inst_Type type;
    Word operand;
} Inst;

typedef struct {
    Word stack[STACK_CAP];
    size_t stack_size;
    
    Inst program[PROGRAM_CAP];
    int ip;

    bool halted;
} Svm;

Inst svm_dump(Svm *svm) {
    printf("stack: \n");
    if (svm->stack_size > 0) {
        for (size_t i = 0; i < svm->stack_size; i++) {
            printf("%ld\n", svm->stack[i]);
        }
    } else {
        printf("empty stack \n");
    }
}

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
};

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

        case INST_ADD: 
            return "inst_add";
        case INST_SUB:
            return "inst_sub";
        case INST_DIV:
            return "inst_div";
        case INST_MUL:
            return "inst_mul";

        case INST_BRNZ:
            return "inst_brnz";
        case INST_JMP:
            return "inst_jmp";
        case INST_HALT: 
            return "inst_halt";
        case INST_EQ:
            return "inst_eq";
        case INST_NQ:
            return "inst_nq";

    }
}

const char *print_inst_as_cstr(FILE *file, Inst *inst) {
   fprintf(file, "Inst {\n type = %s, \n operand = %ld\n}\n", inst_type_as_cstr(inst->type), inst->operand); 
}

Trap svm_execute_inst(Svm *svm)  {
    if (svm->stack_size >= STACK_CAP)   {
        return TRAP_STACK_OVERFLOW; 
    }; 
    
    Inst inst = svm->program[svm->ip];

    switch (inst.type)  {
        case INST_PUSH: {
           svm->stack[svm->stack_size++] = inst.operand;                        
           svm->ip += 1;
        } break;
        case INST_SWAP: {
            if (svm->stack_size < inst.operand) {
                return TRAP_STACK_UNDERFLOW;
            };

            const uint64_t a = svm->stack_size - 1;
            const uint64_t b = svm->stack_size - (1 + inst.operand);

            Word t = svm->stack[a];
            svm->stack[a] = svm->stack[a];
            svm->stack[b] = t;

            svm->ip += 1;
        } break;
        case INST_POP: {
            if (svm->stack_size < 1) {
                return TRAP_STACK_UNDERFLOW;
            };
            svm->stack_size--;         
            svm->ip++;
        } break;
        case INST_DUP: {
           if (svm->stack_size < 1) {
                return TRAP_STACK_UNDERFLOW; 
           };     

           svm->stack[svm->stack_size] = svm->stack[svm->stack_size - 1 - inst.operand];
           svm->stack_size += 1;
           svm->ip += 1;
        } break;

        case INST_ADD: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }
            
            svm->stack[svm->stack_size - 2] += svm->stack[svm->stack_size - 1];
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_SUB: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            } 

            svm->stack[svm->stack_size - 2] -= svm->stack[svm->stack_size - 1];
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_MUL: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size -2] *= svm->stack[svm->stack_size -1];
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_DIV: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            }               

            svm->stack[svm->stack_size -2] /= svm->stack[svm->stack_size -1];
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;

        case INST_JMP: {
            svm->ip = inst.operand; 
        } break;
        case INST_HALT: {
            svm->halted = true;        
        } break;
        case INST_BRNZ: {
            if (svm->stack_size < 1) {
                return TRAP_STACK_UNDERFLOW;
            };              

            if (svm->stack[svm->stack_size - 1] != 0) {
                svm->ip = inst.operand;
            } else {
                svm->ip += 1; 
            };

            svm->stack_size -= 1;
        } break;
        case INST_EQ: {
            if (svm->stack_size < 2) {
               return TRAP_STACK_UNDERFLOW;
            };              

            svm->stack[svm->stack_size - 2] = svm->stack[svm->stack_size - 1] == svm->stack[svm->stack_size - 2];

            svm->ip++;
            svm->stack_size -= 1;
        } break;
        case INST_NQ: {
            if (svm->stack_size < 2) {
                return TRAP_STACK_UNDERFLOW;
            };              
    
            svm->stack[svm->stack_size - 2] = svm->stack[svm->stack_size - 1] != svm->stack[svm->stack_size - 2];
            svm->ip += 1;
            svm->stack_size = svm->stack_size - 1;
        } break;
    };

    return NO_TRAP;
}

#define SVM_MAKE_PUSH(value) ((Inst) { .type = INST_PUSH, .operand = (value) })
#define SVM_MAKE_ADD() ((Inst) { .type = INST_ADD })
#define SVM_MAKE_SUB() ((Inst) { .type = INST_SUB })
#define SVM_MAKE_MUL() ((Inst) { .type = INST_MUL })
#define SVM_MAKE_DIV() ((Inst) { .type = INST_DIV })
#define SVM_MAKE_JMP(value) ((Inst) { .type = INST_JMP, .operand = (value) })
#define SVM_MAKE_HALT() ((Inst) { .type = INST_HALT })
#define SVM_MAKE_SWAP(value) ((Inst) { .type = INST_SWAP, .operand = (value) })
#define SVM_MAKE_POP() ((Inst) { .type = INST_POP })
#define SVM_MAKE_DUP(value) ((Inst) {   .type = INST_DUP, .operand = (value) })
#define SVM_MAKE_BRNZ(value) ((Inst) { .type = INST_BRNZ, .operand = (value)    })
#define SVM_MAKE_EQ() ((Inst) { .type = INST_EQ })
#define SVM_MAKE_NQ() ((Inst) { .type = INST_NQ })

#define ARRAY_SIZE(xs) (sizeof(xs) / ((sizeof(xs)[0])))

Inst program[] = {
    SVM_MAKE_PUSH(1), // 0
    SVM_MAKE_PUSH(1), // 1
    SVM_MAKE_ADD(),   // 2
    SVM_MAKE_DUP(0),  // 3
    SVM_MAKE_PUSH(13), // 4
    SVM_MAKE_EQ(),    // 5
    SVM_MAKE_BRNZ(8), // 6
    SVM_MAKE_JMP(1),  // 7
    SVM_MAKE_HALT(),  // 8
};

void svm_execute_program(Svm *svm, int limit)   {
    while (limit != 0 && !svm->halted)  {
        Trap trap = svm_execute_inst(svm);
        if (trap != NO_TRAP) {
            fprintf(stderr, "Error: %s\n", trap_as_cstr(trap));
            print_inst_as_cstr(stdout, &svm->program[svm->ip]);
            exit(1);
        };

        if (limit > 0) {
            limit--;
        };
    }    
}

int main(void) {

    Svm svm = {0};

    for (size_t i = 0; i < ARRAY_SIZE(program); ++i) {
       svm.program[i] = program[i];
    };

    svm_execute_program(&svm, 500);
   
    svm_dump(&svm); 
    
    return 0;
}

