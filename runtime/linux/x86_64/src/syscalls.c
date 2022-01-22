#include "syscalls.h"

ssize_t read(int fd, void *buf, size_t count) {
    /* Read syscalls returns the amount of bytes read in a signed integer, 
    to follow along with libc's we use a signed version of size_t aswell */
    ssize_t ret_read;

    asm(
        "mov rax, 0;"
        "syscall;"
        : "=r" (ret_read)
        : "r" (fd), "r" (buf), "r" (count)
        : "rdi", "rsi", "rdx"
    );

    return ret_read;
}

int write(int fd, const char *buf, size_t size) {
    int ret_code;

    asm(
        "mov rax, 1;"         
        "syscall;"
        : "=r" (ret_code) 
        : "r" (fd), "r" (buf), "r" (size)
        : "rdi", "rsi", "rdx"
    );

    return ret_code;
}

int open(const char *filename, int flags, uint64_t mode) {
    int fd; 
   
    asm(
        "mov rax, 2;"
        "syscall;"
        : "=r" (fd)
        : "r" (filename), "r" (flags), "r" (mode)
        : "rdi", "rsi", "rdx"
    );

    return fd;
}

int close(int fd) {
    int ret_code;

    asm(
        "mov rax, 3;"
        "syscall;"
        : "=r" (ret_code)
        : "r" (fd)
        : "rdi"
    );

    return ret_code;
}

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
    void *ret_address;

    asm(
        "mov rax, 9;"
        "syscall;"       
        : "=r" (ret_address)
        : "r" (addr), "r" (length), "r" (prot), "r" (flags), "r" (fd), "r" (offset)
        : "rdi", "rsi", "rdx", "r10", "r8", "r9"
    );

    return ret_address;
}

int mprotect(void *addr, size_t length, int prot) {
    int ret_code;

    asm(
        "mov rax, 10;"        
        "syscall;"
        : "=r" (ret_code)
        : "r" (addr), "r" (length), "r" (prot)
        : "rdi", "rsi", "rdx"
    );

    return ret_code;
}

int munmap(void *addr, size_t length) {
    int ret_code;
    
    asm(
        "mov rax, 11;"         
        "syscall;"
        : "=r" (ret_code)
        : "r" (addr), "r" (length)
        : "rdi", "rsi"
    );

    return ret_code;
}

void exit(int code) {
    asm(
        "mov rax, 60;"
        "syscall;"
        :
        : "r" (code)
        : "rbx" 
    );
}
