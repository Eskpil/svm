BITS 64

segment .text
    global _start
    _start:
        mov rdx, __?float32?__(1.5)
        mov rsi, __?float32?__(1.25)
        mov xmm1, rdx
        mov xmm2, rsi
        fadd xmm1, xmm2
    exit:
        mov rax, 60
        mov rdi, 0
        syscall
