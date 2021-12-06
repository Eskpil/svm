#ifndef SVM_H_
#define SVM_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include "./word.h"
#include "./inst.h"

#define STACK_CAP 8192
#define PROGRAM_CAP 65565

typedef uint64_t Inst_Addr;

typedef enum {
    NO_TRAP,
    TRAP_STACK_OVERFLOW,
    TRAP_STACK_UNDERFLOW,
    TRAP_DIV_ZERO,
} Trap;

typedef struct {
    Word stack[STACK_CAP];
    uint64_t stack_size;

    Inst program[PROGRAM_CAP];
    Inst_Addr ip;

    bool halted;
} Svm;

void svm_dump(FILE *file, const Svm *svm);
void svm_execute_program(Svm *svm, int limit);
const char *trap_as_cstr(Trap trap);
Trap svm_execute_inst(Svm *svm);

#endif
