BITS 64

segment .text
    global _start
    _start:
        fmov xmm0, 1.5
        fmov xmm1, 1.25
        fadd xmm0, xmm1 
    exit:
        mov rax, 60
        mov rdi, 0
        syscall
