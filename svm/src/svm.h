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
#define EXTERNAL_NATIVE_CAP 65565
#define NATIVE_NAME_CAP 255
#define NATIVE_CAP 4096

typedef uint64_t Inst_Addr;
typedef enum {
    NO_TRAP,
    TRAP_STACK_OVERFLOW,
    TRAP_STACK_UNDERFLOW,
    TRAP_DIV_ZERO,
} Trap;

typedef struct Svm Svm;

typedef Trap (*Svm_Native)(Svm*);
typedef struct {
    char name[NATIVE_NAME_CAP];
    uint64_t index;
} External_Native;

struct Svm {
    Word stack[STACK_CAP];
    uint64_t stack_size;

    Inst program[PROGRAM_CAP];
    Inst_Addr ip;

    Svm_Native natives[NATIVE_CAP];
    size_t natives_size;

    External_Native exteranls[EXTERNAL_NATIVE_CAP];
    size_t externals_size;

    bool halted;
};

void svm_dump(FILE *file, const Svm *svm);
void svm_execute_program(Svm *svm, int limit);
const char *trap_as_cstr(Trap trap);
Trap svm_execute_inst(Svm *svm);

#endif
