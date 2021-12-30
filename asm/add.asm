BITS 64

segment .text
    global _start
    _start:
       mov rax, 10
       mov rdi, 20
       add rax, rdi
       jmp exit 
    exit:
        xor rax, rax
        xor rdi, rdi
        mov rax, 60
        mov rdi, 0
        syscall
