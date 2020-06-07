#include <programs.h>
#include <programHandler.h>
#include <libC.h>
#include <shell.h>
#define CANT_FUNC 9

void printTime();
void printCPUInfo();
void printTemperature();
void inforeg();
void test0();
void test();
void testScanf();
void test6();

char functions[CANT_FUNC][20] = {"printTime", "printTemperature","printCPUInfo", "inforeg", "test0", "test", "testScanf", "test6"};
void (*func_ptr[CANT_FUNC])() = {printTime, printTemperature, printCPUInfo, inforeg, test0, test, testScanf, test6};


static char input[WIDTH/8] = {0};
static int pos = 0;
static retFlag = 0;

void initShell() {
    // promt message
    printUser();
}

void shell(char key) {
    if (key == '\n') {
        putChar('\n');
        if (pos != 0) {
            int j;
            for (j = 0; j < CANT_FUNC && !strcmp(input, functions[j]); j++) {}
            if (j < CANT_FUNC) {
                func_ptr[j]();
            } else {
                printError("Not a valid function\n");
            }
            input[0] = 0;
            pos = 0;
        }
        printUser();
    } else if (key == DELETE) {
        if (pos != 0) {
            putChar(key);
            pos--;
            input[pos] = 0;
        }
    } else {
        putChar(key);
        input[pos++] = key;
        input[pos] = 0;
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