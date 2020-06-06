#include <libC.h>

static char * regs[] = {
	"r15: ", "r14: ", "r13: ", "r12: ", "r11: ", 
	"r10: ", "r9: ", "r8: ", "rsi: ", "rdi: ", 
	"rbp: ", "rdx: ", "rcx: ", "rbx: ", "rax: ", 
	"rip: ", "cs: ", "rsp: "
	};

void inforeg() {
    uint64_t memory[18];
    getRegisters(memory);
    for (int i = 0; i < 18; i++) {
        printf("%s: %d\n", regs[i], memory[i]);
    }
}