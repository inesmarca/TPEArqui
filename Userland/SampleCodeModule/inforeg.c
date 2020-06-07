#include <libC.h>
extern void getRegisters(uint64_t * buff) ;


static char * regs[] = {
	"R15:   ", "R14:   ", "R13:   ", "R12:   ", "R11:   ", 
	"R10:   ", "R9:    ", "R8:    ", "RSI:   ", "RDI:   ", 
	"RBP:   ", "RDX:   ", "RCX:   ", "RBX:   ", "RAX:   ", 
	"RIP:   ", "CS:    ", "FLAGS: ", "RSP:   "
	};

void inforeg() {
    uint64_t memory[19];
    char buff[9] = {0};
    getRegisters(memory);
    for (int i = 0; i < 19; i++) {
        uintToBase(memory[i], buff, 16);
        baseToHexa(buff);
        printf("%s %s", regs[i], buff);
        if (i % 2 == 0) {
            putChar('\n');
        } else {
            printf("            ");
        }
    }
}