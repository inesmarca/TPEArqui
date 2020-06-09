#include <programs.h>
#include <programHandler.h>
#include <libC.h>
#include <shell.h>
#include <libFun.h>
#include <sysLib.h>
#define CANT_FUNC 10

void help();

char functions[CANT_FUNC][20] = {"help","printTime", "printTemperature","printCPUInfo", "inforeg", "triggerException0", "triggerException6","printmem", "clear"};
void (*func_ptr[CANT_FUNC])() = { help , printTime,   printTemperature,  printCPUInfo,   inforeg,   triggerException0,   triggerException6,  printmem , clear};
char parameters[CANT_FUNC]    = { 0,     0,           0,                 0,              0,         0,       0,      1        , 0       };

static char input[DIM_BUFFER] = {0};
static int pos = 0;


void initShell() {
    printf("Bienvenido %s!\n",getUser());
    printf("Para comenzar, ingrese un comando o presione la tecla TAB para cambiar de programa\n");
    printf("Para una lista de los programas disponibles ingrese help\n");
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
            pos--;
            input[pos] = 0;
            putChar(key);
        }
    } else {
        putChar(key);
        input[pos++] = key;
        input[pos] = 0;
    }
}

void help(){
    printf("La shell esta equipada con los siguientes Programas, para ejectutarlos ingrese el nombre del programa en la linea de comando \n");
    for (int i = 0; i < CANT_FUNC; i++) {
        if (i % 4 == 0) {
            putChar('\n');
        }
        printf("%s ",functions[i]);
        if (parameters[i] != 0) {
            if (parameters[i] == 1) {
                printf(" (espera %d parametro)", parameters[i]);
            } else {
                printf(" (espera %d parametros)", parameters[i]);
            }   
        }
    }
    putChar('\n');
    printf("Para informacion adicional, consultar documentacion.\n");
}