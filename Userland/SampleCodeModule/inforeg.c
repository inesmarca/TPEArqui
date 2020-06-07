#include <libC.h>

static char * regs[] = {
	"R15:   ", "R14:   ", "R13:   ", "R12:   ", "R11:   ", 
	"R10:   ", "R9:    ", "R8:    ", "RSI:   ", "RDI:   ", 
	"RBP:   ", "RDX:   ", "RCX:   ", "RBX:   ", "RAX:   ", 
	"RIP:   ", "CS:    ", "FLAGS: ", "RSP:   "
	};

void inforeg() {
    uint64_t memory[19];
    getRegisters(memory);
    for (int i = 0; i < 19; i++) {
        printf("%s %d", regs[i], memory[i]);
        if (i % 2 == 0) {
            putChar('\n');
        } else {
            printf("            ");
        }
    }
}