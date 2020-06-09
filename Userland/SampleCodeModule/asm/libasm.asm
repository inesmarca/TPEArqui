GLOBAL readKeyBuff
GLOBAL writeScreen
GLOBAL readPixel
GLOBAL writePixel
GLOBAL getExitFlag
GLOBAL sysChangeScreen
GLOBAL getRTC
GLOBAL getTemperature
GLOBAL getRegisters
GLOBAL clear
GLOBAL setCursor

section .text

; void readKeyBuff(char * buf)
readKeyBuff:
    mov rax, 0
    int 80h
    ret

; void writeScreen(const char * string, int letter_color, int background_color)
writeScreen:
    mov rax, 1
    int 80h
    ret

; void readPixel(int * hexa, int x, int y)
readPixel:
    mov rax, 2
    int 80h
    ret

; void writePixel(int x, int y, int color)
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

; void changeScreen(int screen)
sysChangeScreen:
    mov rax, 5
    int 80h
    ret

;int getTemperature()
getTemperature:
    push rbx
    mov rax,6
    int 80h
    mov rax,rbx
    pop rbx
    ret
	
; void getRegisters(uint64_t * buff) 
getRegisters:
    mov rax, 7
    int 80h
    ret

; void clear()
clear:
    mov rax, 4
    int 80h
    ret

; void setCursor(int x, int y);
setCursor:
    mov rax, 8
    int 80h
    ret

;int getRTC(int x) 
getRTC:
    push rbp
    mov rbp, rsp

    mov rax, 0
    mov rax, rdi
    out 70h, al
    in al, 71h

    mov rsp, rbp
    pop rbp
    ret