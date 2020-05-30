GLOBAL readKeyBuff
GLOBAL writeScreen
GLOBAL readPixel
GLOBAL writePixel
GLOBAL getExitFlag
GLOBAL getActiveScreen

; void readKeyBuff(char * buf)
readKeyBuff:
    mov rax, 0
    int 80h
    ret

; void writeScreen(const char * string)
writeScreen:
    mov rax, 1
    int 80h
    ret

; void readPixel(char * rgb, int x, int y)
readPixel:
    mov rax, 2
    int 80h
    ret

; void writePixel(int x, int y, int red, int green, int blue)
writePixel:
    mov rax, 3
    int 80h
    ret

; int getExitFlag()
getExitFlag:
    push rbx
    mov rax, 4
    int 80h
    mov rax, rbx
    pop rbx
    ret

; int getActiveScreen()
getActiveScreen:
    push rbx
    mov rax, 5
    int 80h
    mov rax, rbx
    pop rbx
    ret
