#ifndef WORD_H_
#define WORD_H_

#include <stdint.h>

typedef union { 
    int64_t as_i64;
    uint64_t as_u64;
    double as_f64;
    void *as_ptr;
} Word;

#endif
