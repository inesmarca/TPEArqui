#include <shell.h>
#include <sysLib.h>
#include <libC.h>
#include <calculator.h>
#include <cpuInfo.h>
#include <stdint.h>

#define B_SPACE 0x0E
#define CURSOR 127

extern char * cpuVendor();
extern char * cpuModel();
char inputBuffer[128] = {0};
char input1[128] = {0};
int pos1 = 0;
char input2[128] = {0};
int pos2 = 0;

void printTime();
void printCPUInfo();
void printTemperature();
void inforeg();
void test0();
void test();

char username[20] = {0};

char functions[6][20] = {"printTime", "printTemperature","printCPUInfo", "inforeg", "test0", "test"};
void (*func_ptr[6])() = {printTime, printTemperature, printCPUInfo, inforeg, test0, test};

void shell() {
    while (!getExitFlag()) {
        while (getActiveScreen() == 1) {
            readKeyBuff(inputBuffer);
            for (int i = 0; inputBuffer[i] != 0; i++) {
                if (inputBuffer[i] == '=') {
                    putChar(inputBuffer[i]);
                    input1[pos1++] = inputBuffer[i];
                    char * result=runCalc(input1);
                    if (result!=NULL)
                    {
                       printf("%s %s\n", inputBuffer[i],result);
                    }
                    else
                    {
                        printf("%s\n", inputBuffer[i]);
                    }                  
                    input1[0] = 0;
                    pos1 = 0;
                } else if (inputBuffer[i] == B_SPACE) {
                    putChar(inputBuffer[i]);
                    inputBuffer[i] = 0;
                    pos1--;
                    input1[pos1] = 0;
                } else if (inputBuffer[i] == 'D') {  // borra la linea entera
                    while (pos1 != 0) {
                        putChar(B_SPACE);
                        pos1--;
                    }
                    input1[pos1] = 0;
                } else if (inputBuffer[i] != '\n') {
                    putChar(inputBuffer[i]);
                    input1[pos1++] = inputBuffer[i];
                    input1[pos1] = 0;
                    inputBuffer[i] = 0;
                } else {
                    inputBuffer[i] = 0;
                }
            } 
        }

        while (getActiveScreen() == 2) {
            readKeyBuff(inputBuffer);
            for (int i = 0; inputBuffer[i] != 0; i++) {
                if (inputBuffer[i] == '\n') {
                    putChar('\n');
                    int j;
                    for (j = 0; j < 6 && !strcmp(input2, functions[j]); j++) {}
                    if (j != 6) {
                        func_ptr[j]();
                    } else {
                        printf("Not a valid function\n");
                    }
                    input2[0] = 0;
                    pos2 = 0;
                } else if (inputBuffer[i] == B_SPACE) {
                    putChar(inputBuffer[i]);
                    inputBuffer[i] = 0;
                    pos2--;
                    input2[pos2] = 0;
                } else {
                    putChar(inputBuffer[i]);
                    input2[pos2++] = inputBuffer[i];
                    input2[pos2] = 0;
                    inputBuffer[i] = 0;
                }
            }
        }
    }
}

void inforeg() {
    uint64_t memory[18];
    getRegisters(memory);
    for (int i = 0; i < 18; i++) {
        printf("%d, ", memory[i]);
    }
    putChar('\n');
}

void test0() {
    int x = 5 / 0;
}