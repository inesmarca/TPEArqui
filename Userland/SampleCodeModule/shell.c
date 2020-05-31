#include <shell.h>
#include <sysLib.h>
#include <libC.h>

#define B_SPACE 0x0E

extern char * cpuVendor();
extern char * cpuModel();
char inputBuffer = 0;
char input1[128] = {0};
int pos1 = 0;
char input2[128] = {0};
int pos2 = 0;

void help();
void inforeg();
void printmem();
void printTime();
void cpuInfo();
void getTemperature();

char functions[1][20] = {"printTime"};
void (*func_ptr[1])() = {printTime};

void shell() {
    while (!getExitFlag()) {
        while (getActiveScreen() == 1) {
            readKeyBuff(&inputBuffer);
            if (inputBuffer != 0) {
                if (inputBuffer == '\n') {
                    // runCalc();
                } else if (inputBuffer == B_SPACE) {
                    printf(&inputBuffer);
                    inputBuffer = 0;
                    pos1--;
                    input1[pos1] = 0;
                } else if (inputBuffer == 'D') {  // borra la linea entera
                    while (pos1 != 0) {
                        putChar(B_SPACE);
                        pos1--;
                    }
                    input1[pos1] = 0;
                } else {
                    printf(&inputBuffer);
                    input1[pos1++] = inputBuffer;
                    input1[pos1] = 0;
                    inputBuffer = 0;
                }
            }
        }
        while (getActiveScreen() == 2) {
            readKeyBuff(&inputBuffer);
            if (inputBuffer != 0) {
                if (inputBuffer == '\n') {
                    int j = pos2;
                    while (j != 0) {
                        putChar(B_SPACE);
                        j--;
                    }
                    int i;
                    for (i = 0; i < 6 && !strcmp(input2, &functions[i]); i++) {}
                    if (i != 6) {
                        func_ptr[i]();
                    }
                } else if (inputBuffer == B_SPACE) {
                    printf(&inputBuffer);
                    inputBuffer = 0;
                    pos2--;
                    input2[pos2] = 0;
                } else {
                    printf(&inputBuffer);
                    input2[pos2++] = inputBuffer;
                    input2[pos2] = 0;
                    inputBuffer = 0;
                }
            }
        }
    }
}