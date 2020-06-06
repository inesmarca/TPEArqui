#include <stdint.h>
#include <lib.h>

static char * regs[] = {
	"r15: ", "r14: ", "r13: ", "r12: ", "r11: ", 
	"r10: ", "r9: ", "r8: ", "rsi: ", "rdi: ", 
	"rbp: ", "rdx: ", "rcx: ", "rbx: ", "rax: ", 
	"rip: ", "cs: ", "rsp: "
	};

uint64_t memory[18] = {0};

void saveReg(uint64_t * stackFrame) {
    for (int i = 0; i < 17; i++) {
        memory[i] = stackFrame[i];
    }
    memory[17] = stackFrame[18];
}

uint16_t * getVec() {
    return memory;
}