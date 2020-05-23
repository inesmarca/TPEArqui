GLOBAL test
section .text

test:
    push rbp
	mov rbp,rsp

    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, len
    int 80h

	pop rbp
	mov rsp,rbp
	popState
	ret

section .data
msg db "HOLA BUENAS NOCHES",10
len equ $-msg