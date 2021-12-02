#include <stdio.h>
#include <stdint.h>

#define STACK_CAP 8192

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

Inst svm_inst_push(Word operand) {
    return (Inst) {
        .type = INST_PUSH,
        .operand = operand,
    };
}


Inst svm_inst_mul() {
    return (Inst) {
        .type = INST_MUL,
        .operand = 0 
    };
}


Inst svm_inst_div() {
    return (Inst) {
        .type = INST_DIV,
        .operand = 0 
    };
}



Inst svm_inst_add() {
    return (Inst) {
        .type = INST_ADD,
        .operand = 0
    };
}

Inst svm_inst_sub() {
    return (Inst) {
        .type = INST_SUB,
        .operand = 0,
    };
}

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

int main(void) {

    Svm svm = {0};
    
    svm_dump(&svm);
    svm_execute_inst(&svm, svm_inst_push(420));
    svm_dump(&svm);
    svm_execute_inst(&svm, svm_inst_push(69));
    svm_dump(&svm);
    svm_execute_inst(&svm, svm_inst_sub());
    svm_dump(&svm);
    svm_execute_inst(&svm, svm_inst_push(2));
    svm_dump(&svm);
    svm_execute_inst(&svm, svm_inst_mul());
    svm_dump(&svm);
    svm_execute_inst(&svm, svm_inst_push(3));
    svm_dump(&svm);
    svm_execute_inst(&svm, svm_inst_div());
    svm_dump(&svm);
    return 0;
}

