BITS 64

segment .text
    global _start
    _start:
        push 10
        push 20
        pop rdx
        pop rax
        add rax, rdx       
        jmp exit

    exit:
        xor rax, rax
        xor rdi, rdi
        mov rax, 60
        mov rdi, 0
        syscall 
