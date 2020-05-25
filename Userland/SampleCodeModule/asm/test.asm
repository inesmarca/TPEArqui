GLOBAL test
section .text

test:
    push rbp
	mov rbp,rsp
    mov rax, 0

.loop:
    mov rax, 2
    int 80h
    cmp rbx, 1
    jne .loop

    mov rax, 0
    mov rdi, 0
    mov rsi, str
    mov rdx, 15
    int 80h

    mov rax, 1
    mov rdi, 1
    int 80h

	mov rsp,rbp
    pop rbp
	ret

section .data
msg db "HOLA BUENAS NOCHES",10
len equ $-msg
fmt db "%s", 10, 0

section .bss
str: resb 15
string: resb 12