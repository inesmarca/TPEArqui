GLOBAL readKeyBuff
GLOBAL writeScreen
GLOBAL readPixel
GLOBAL writePixel
GLOBAL getExitFlag
GLOBAL getActiveScreen
GLOBAL cpuVendor
GLOBAL cpuModel
GLOBAL getRTC
GLOBAL getTemprerature






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

;int getTemprerature()
getTemprerature:
    push rbx
    mov rax,6
    int 80h
    mov rax,rbx
    pop rbx
    ret
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

cpuModel:       ; Me parece que esta mal
    push rbp
	mov rbp, rsp

    mov rax, 1
    cpuid

    mov [rdi], rax
    mov byte [rdi+8], 0
    mov rax, 0
    mov rax, rdi

    mov rsp, rbp
	pop rbp
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
    

