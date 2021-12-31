; Tests for the .bss segment of elf file

segment .text
    global _start
    _start:
        mov rdx, 10
        mov [test1], rdx
        mov [test2], rdx
        mov [test3], rdx
        jmp exit
    exit:
        mov rax, 60
        mov rdi, 0
        syscall


segment .bss
    test1: resq 8
    test2: resq 8
    test3: resq 8
