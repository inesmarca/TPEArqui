#include <stdint.h>
#include <lib.h>

static char * regs[] = {
	"R15:   ", "R14:   ", "R13:   ", "R12:   ", "R11:   ", 
	"R10:   ", "R9:    ", "R8:    ", "RSI:   ", "RDI:   ", 
	"RBP:   ", "RDX:   ", "RCX:   ", "RBX:   ", "RAX:   ", 
	"RIP:   ", "CS:    ", "FLAGS: ", "RSP:   "
	};

uint64_t memory[19] = {0};

void saveReg(uint64_t * stackFrame) {
    for (int i = 0; i < 19; i++) {
        memory[i] = stackFrame[i];
    }
}

uint16_t * getVec() {
    return memory;
}