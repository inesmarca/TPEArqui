#include <programs.h>
#include <programHandler.h>
#include <libC.h>
#include <shell.h>
#include <printmem.h>
#define CANT_FUNC 9

void printTime();
void printCPUInfo();
void printTemperature();
void inforeg();
void test0();
void test6();

char functions[CANT_FUNC][20] = {"printTime", "printTemperature","printCPUInfo", "inforeg", "test0", "test6","printmem"};
void (*func_ptr[CANT_FUNC])() = { printTime,   printTemperature,  printCPUInfo,   inforeg,   test0,   test6,  printmem };
char parameters[CANT_FUNC]    = { 0,           0,                 0,              0,         0,       0,      1        };

static char input[DIM_BUFFER] = {0};
static int pos = 0;


void initShell() {
    // promt message
    printUser();
}

void shell(char key) {
    if (key == '\n') {
        putChar('\n');
        if (pos != 0) {
            int j;
            int k=0;
            
            char aux[DIM_BUFFER];
            while (input[k] != ' ' && input[k] != 0)
            {
                aux[k]=input[k];
                k++;
            }
            aux[k]=0;
            
            for (j = 0; j < CANT_FUNC && !strcmp(aux, functions[j]) ; j++) {}
            if (j < CANT_FUNC) {
                if (parameters[j==0])
                {
                     func_ptr[j]();
                }
                int d=0;
                k++;
                while (input[k]!=0) //copio solo los parametros
                {
                    aux[d++]=input[k++];
                }
                aux[d]=0;
                func_ptr[j](aux);
               
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