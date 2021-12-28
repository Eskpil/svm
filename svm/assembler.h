#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#define BYTECODE_CAP 65565
    
typedef struct {
   uint8_t bytecode[BYTECODE_CAP];
   size_t count;
   void *assigned;
   size_t mem_size;
   bool finalized;
} Assembler;

void assembler_map_mem(Assembler *asembler);
void assembler_finalize(Assembler *assembler);
void assembler_load_bytecode(Assembler *assembler);
void assembler_load_u8(Assembler *assembler, uint8_t value);
void assembler_unmap_mem(Assembler *assembler);

#endif
