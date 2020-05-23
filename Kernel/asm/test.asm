GLOBAL test
section .text

test:
    push rbp
	mov rbp,rsp

    mov rax, 0
    mov rdi, 1
    mov rsi, str
    mov rdx, 15
    int 80h

    mov rax, 1
    int 80h

	mov rsp,rbp
    pop rbp
	ret

section .data
msg db "HOLA BUENAS NOCHES",10
len equ $-msg

section .bss
str: resb 15