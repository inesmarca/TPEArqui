#include <consoleManager.h>
#include <stdint.h>
#include <lib.h>
#define ZERO_EXCEPTION_ID 0

static void zero_division();

uint64_t * ipReturn;
uint64_t * rspReturn;

static char * regs[] = {
	"r15: ", "r14: ", "r13: ", "r12: ", "r11: ", 
	"r10: ", "r9: ", "r8: ", "rsi: ", "rdi: ", 
	"rbp: ", "rdx: ", "rcx: ", "rbx: ", "rax: ", 
	"rip: ", "cs: ", "rsp: "
	};

void printRegs(uint64_t * stackFrame) {
	char buffer[20];
	for (int i = 0; i < 17; i++) {
		print(regs[i], LETTER_COLOR, BACKGROUND_COLOR);
		uintToBase(stackFrame[i], buffer, 16);
		print(buffer, LETTER_COLOR, BACKGROUND_COLOR);
		newLine(BACKGROUND_COLOR);
	}
	print(regs[17], LETTER_COLOR, BACKGROUND_COLOR);
	uintToBase(stackFrame[18], buffer, 16);  // RSP
	print(buffer, LETTER_COLOR, BACKGROUND_COLOR);
	newLine(BACKGROUND_COLOR);
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
}

static void zero_division(uint64_t * stackFrame) {
	print("Exception 0: division by 0\n", LETTER_COLOR, BACKGROUND_COLOR);
	printRegs(stackFrame);
	resetScreen(stackFrame);
}