#include <programs.h>
#include <programHandler.h>
#include <libC.h>
#define CANT_FUNC 7

void printTime();
void printCPUInfo();
void printTemperature();
void inforeg();
void test0();
void test();
void testScanf();

char functions[CANT_FUNC][20] = {"printTime", "printTemperature","printCPUInfo", "inforeg", "test0", "test", "testScanf"};
void (*func_ptr[CANT_FUNC])() = {printTime, printTemperature, printCPUInfo, inforeg, test0, test, testScanf};

void shell() {
    static char input[WIDTH/8] = {0};
    static int pos = 0;
    static char inputBuffer[128] = {0};
    int retFlag = 0;
    while (!retFlag) {
        readKeyBuff(inputBuffer, DIM_BUFFER);
        for (int i = 0; inputBuffer[i] != 0; i++) {
            if (inputBuffer[i] == TAB) {
                inputBuffer[i];
                retFlag = 1;
            } else if (inputBuffer[i] == '\n') {
                putChar('\n');
                int j;
                for (j = 0; j < CANT_FUNC && !strcmp(input, functions[j]); j++) {}
                if (j != CANT_FUNC) {
                    func_ptr[j]();
                } else {
                    printf("Not a valid function\n");
                }
                input[0] = 0;
                pos = 0;
            } else if (inputBuffer[i] == DELETE && pos != 0) {
                putChar(inputBuffer[i]);
                inputBuffer[i] = 0;
                pos--;
                input[pos] = 0;
            } else {
                putChar(inputBuffer[i]);
                input[pos++] = inputBuffer[i];
                input[pos] = 0;
                inputBuffer[i] = 0;
            }
            inputBuffer[i]=0;
        }
    }
}

void test0() {
    int x = 5 / 0;
}

void testScanf() {
    char string[10];
    int x = 0;
    char * aux="%s";
    scanf(aux, &string);
    printf("%s\n", &string);
}