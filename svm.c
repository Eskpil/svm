#include <stdio.h>
#include <stdint.h>

#define STACK_CAP 8192

typedef enum {
    NO_ERR,
    ERR_STACK_OVERFLOW,
    ERR_STACK_UNDERFLOW,
} Err;

typedef int64_t Word; 

typedef enum {
    INST_PUSH,
    INST_ADD,
    INST_SUB,
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

Err svm_execute_inst(Svm *svm, Inst inst)  {
    if (svm->stack_size >= STACK_CAP)   {
        return ERR_STACK_OVERFLOW; 
    }; 
    switch (inst.type)  {
        case INST_PUSH: {
           svm->stack[svm->stack_size++] = inst.operand;                        
           svm->ip += 1;
        } break;
        case INST_ADD: {
            if (svm->stack_size < 2) {
                return ERR_STACK_UNDERFLOW;
            }
            
            svm->stack[svm->stack_size - 2] += svm->stack[svm->stack_size - 1];
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
        case INST_SUB: {
            if (svm->stack_size < 2) {
                return ERR_STACK_UNDERFLOW;
            } 

            svm->stack[svm->stack_size - 2] -= svm->stack[svm->stack_size - 1];
            svm->stack_size -= 1;
            svm->ip += 1;
        } break;
    };

    return NO_ERR;
}

Inst svm_inst_push(Word operand) {
    return (Inst) {
        .type = INST_PUSH,
        .operand = operand,
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
    
    return 0;
}

