
#include <libC.h>

extern int cpuModel();
extern char * cpuVendor();

int CPUModel(){
    int aux=cpuModel(); //4:7
    aux=aux & 0x000000F0;
    aux=aux>>4;
    return aux;
}

void printCPUInfo(){
    printf("CPU Vendor is :%s and the model number:%d",cpuVendor(),CPUModel());
}

