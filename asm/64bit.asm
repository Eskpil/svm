BITS 64

segment .text
    global _start
    _start:
        mov rdx, 0x0fffffffffffffff ;9223372036854775807
        mov rsi, 1
        add rdx, rsi
        jmp exit
    exit:
        mov rax, 60
        mov rdi, 0
        syscall
