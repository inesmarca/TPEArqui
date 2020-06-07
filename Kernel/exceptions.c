#include <consoleManager.h>
#include <stdint.h>
#include <lib.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6

static void zero_division();
static void invalid_opcode();

uint64_t * ipReturn;
uint64_t * rspReturn;

static char * regs[] = {
	"R15:   ", "R14:   ", "R13:   ", "R12:   ", "R11:   ", 
	"R10:   ", "R9:    ", "R8:    ", "RSI:   ", "RDI:   ", 
	"RBP:   ", "RDX:   ", "RCX:   ", "RBX:   ", "RAX:   ", 
	"RIP:   ", "CS:    ", "FLAGS: ", "RSP:   "
	};

void printRegs(uint64_t * stackFrame) {
	char buffer[9];
	for (int i = 0; i < 19; i++) {
		print(regs[i], LETTER_COLOR, BACKGROUND_COLOR);
		uintToBase(stackFrame[i], buffer, 16);
		baseToHexa(buffer);
		print(buffer, LETTER_COLOR, BACKGROUND_COLOR);
		if (i % 2 == 0) {
			newLine(BACKGROUND_COLOR);
		} else {
			print("           ", LETTER_COLOR, BACKGROUND_COLOR);
		}
	}
}

void setAddresses(uint64_t * ip, uint64_t * rsp) {
	ipReturn = ip;
	rspReturn = rsp;
}

void resetScreen(uint64_t * stackFrame) {
	stackFrame[15] = ipReturn;
	stackFrame[18] = rspReturn;
}

void exceptionDispatcher(int exception, uint64_t * stackFrame) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(stackFrame);
	else if (exception == INVALID_OPCODE_EXCEPTION_ID)
		invalid_opcode(stackFrame);
}

static void zero_division(uint64_t * stackFrame) {
	print("Exception 0: division by 0\n", LETTER_COLOR, BACKGROUND_COLOR);
	printRegs(stackFrame);
	resetScreen(stackFrame);
}

static void invalid_opcode(uint64_t * stackFrame) {
	print("Exception 6: invalid opcode\n", LETTER_COLOR, BACKGROUND_COLOR);
	printRegs(stackFrame);
	resetScreen(stackFrame);
}