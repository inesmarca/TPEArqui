#include <libC.h>
#include <printmem.h>

#define MAX_DIGITS 20

void hexa(char * buff, int dim) {
	char auxStr[5] = "0x00";
	for (int j = 3; j >= 0 && dim != 0; j--) {
		auxStr[j] = buff[dim - 1];
		dim--;
	} 
	for (int k = 0; k < 4; k++) {
		buff[k] = auxStr[k];
	}
}

void printmem(char * parameters){

    long direc = -1;

    int error = sscanf(parameters,"%ld",&direc);
    
    if (error != 1||direc<0) {
        printError("Error en parseo de parametros \n");
        return;
    }
   
    
    unsigned char * mem=(unsigned char *)direc;

    printf("Direccion inicial : %ld",direc);
    
    printf("\n");
    printf("siguientes 32 bytes en direcciones relativas");
    char buff[5] = {0};
    for (int i = 0; i < 32; i++) {
        int dim = uintToBase(mem[i], buff, 16);
        hexa(buff, dim); 
        if (i % 8 == 0) {
            putChar('\n');
        }
        changeLetterColor(0xFEAB8A);
        printf("%d ", i);
        if (i < 10) {
            putChar(' ');
        }
        changeLetterColor(DEFAULT_LETTER_COLOR);
        printf(": %s   ", buff);
    }
    printf("\n");
}