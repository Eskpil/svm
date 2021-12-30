#ifndef BYTECODE_H_
#define BYTECODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "svm.h"

#if defined(__GNUC__) || defined(__clang__)
#  define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#  define EXPORT
#else
#  error "Packed attributes for struct is not implemented for this compiler. This may result in a program working incorrectly. Feel free to fix that and submit a Pull Request to https://github.com/tsoding/bm"
#endif

#define BYTECODE_VERSION 1
#define BYTECODE_MAGIC 0xa4016d40

void bytecode_read(Svm *svm, const char *file_path);

PACK(struct Bytecode_Metadata {
    uint32_t magic;
    uint16_t version;
    uint64_t program_size;
    uint64_t entry;
});

typedef struct Bytecode_Metadata Bytecode_Metadata;

#endif
