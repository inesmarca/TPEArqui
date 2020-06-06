GLOBAL readKeyBuff
GLOBAL writeScreen
GLOBAL readPixel
GLOBAL writePixel
GLOBAL getExitFlag
GLOBAL sysChangeScreen
GLOBAL getRTC
GLOBAL getTemperature
GLOBAL getRegisters

EXTERN printf

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

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

; void readPixel(char * rgb, int x, int y)
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