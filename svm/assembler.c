#include "./assembler.h"

size_t estimate_mem_size(Assembler *assembler) {
    size_t multiplier = sysconf(_SC_PAGE_SIZE);    
    size_t factor = 1, mem_size;

    for (;;) {
        mem_size = factor * multiplier;
        if (assembler->count <= mem_size) {
            break;
        };

        factor++;
    }
    return mem_size;
}

void assembler_map_mem(Assembler *assembler) {
    size_t mem_size = estimate_mem_size(assembler);
    void *mem = mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, 0, 0);
    
    if (mem == MAP_FAILED) {
        fprintf(stderr, "[ERROR] failed to allocated memory because: %s\n", strerror(errno));        
        exit(1);
    }

    assembler->mem_size = mem_size;
    assembler->assigned = mem;
}

void assembler_finalize(Assembler *assembler) {
    mprotect(&assembler->assigned, assembler->mem_size, PROT_READ | PROT_EXEC);
    assembler->finalized = true;
}

void assembler_load_bytecode(Assembler *assembler) {
    if (!assembler->finalized) {
        fprintf(stderr, "You must finalize the assembler before loading the bytecode onto the assigned memory\n");
        exit(1);
    }
    memcpy(&assembler->assigned, assembler->bytecode, assembler->count);
}

void assembler_load_u8(Assembler *assembler, uint8_t value) {
    assembler->bytecode[assembler->count] = value;
    assembler->count += 1;
}

void assembler_unmap_mem(Assembler *assembler) {
    munmap(&assembler->assigned, assembler->mem_size);
}
