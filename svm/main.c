#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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
    INST_PUSH,
    INST_ADD,
    INST_SUB,
    INST_DIV,
    INST_MUL,
} Inst_Type;

typedef struct {
    Inst_Type type;
    Word operand;
} Inst;

typedef struct {
    Word stack[STACK_CAP];
    size_t stack_size;
    int ip;
} Svm;

Trap svm_execute_inst(Svm *svm, Inst inst)  {
    if (svm->stack_size >= STACK_CAP)   {
        return TRAP_STACK_OVERFLOW; 
    }; 
    switch (inst.type)  {
        case INST_PUSH: {
           svm->stack[svm->stack_size++] = inst.operand;                        
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
    };

    return NO_TRAP;
}

#define SVM_MAKE_PUSH(value) ((Inst) { .type = INST_PUSH, .operand = (value) })
#define SVM_MAKE_ADD() ((Inst) { .type = INST_ADD })
#define SVM_MAKE_SUB() ((Inst) { .type = INST_SUB })
#define SVM_MAKE_MUL() ((Inst) { .type = INST_MUL })
#define SVM_MAKE_DIV() ((Inst) { .type = INST_DIV })


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

#define ARRAY_SIZE(xs) (sizeof(xs) / ((sizeof(xs)[0])))

Inst program[] = {
    SVM_MAKE_PUSH(420),
    SVM_MAKE_PUSH(69),
    SVM_MAKE_SUB(),
    SVM_MAKE_PUSH(3),
    SVM_MAKE_MUL(),
    SVM_MAKE_PUSH(3),
    SVM_MAKE_DIV(),
};

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

int main(void) {

    Svm svm = {0};

    for (size_t i = 0; i < ARRAY_SIZE(program); ++i) {
        Trap trap = svm_execute_inst(&svm, program[i]);
        if (trap != NO_TRAP) {
            fprintf(stderr, "Error: %s\n", trap_as_cstr(trap));
            svm_dump(&svm);
            exit(1);
        }
    };

    svm_dump(&svm);
    
    return 0;
}

