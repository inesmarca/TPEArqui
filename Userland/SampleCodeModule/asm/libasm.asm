GLOBAL write
GLOBAL read
GLOBAL getExitFlag
GLOBAL getScreen
GLOBAL writePixel

section .text

write:
    mov rax, 1
    int 80h
    ret

read:
    mov rax, 0
    int 80h
    ret

writePixel:
    mov rax, 4
    int 80h
    ret

getExitFlag:
    push rbx
    mov rax, 2
    int 80h
    mov rax, rbx
    pop rbx
    ret

getScreen:
    push rbx
    mov rax, 3
    int 80h
    mov rax, rbx
    pop rbx
    ret
