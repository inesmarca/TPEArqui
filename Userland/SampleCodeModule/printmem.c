#include <libC.h>

#define MAX_DIGITS 20


int printmem(char * parameters){

    long direc=0;

    int error=sscanf(parameters,"%ld",&direc);
    
    if (error!=1)
    {
        printf("Error en parseo de parametros \n");
        return -1;
    }
    unsigned char * mem=(unsigned char *)direc;

    printf("Direccion inicial : %ld",direc);
    
    printf("\n");
    printf("siguientes 32 bytes en direcciones relativas");
    
    
    
    
    
    
    
    for (int i = 0; i < 32; i++)
    {   
         if (i%8==0)
        {
            printf("\n");
        }
        char aux [MAX_DIGITS];
        int digits=uintToBase(mem[i], aux, 16);
        aux [digits+1]=0;
        printf("%d : 0x%s  ",i,aux);
        
    }
    printf("\n");
    
 
    return 0;
}