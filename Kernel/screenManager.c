#include <video_driver.h>
#include <screenManager.h>
#include <calculator.h>

char buffer1[1024];
int pos1 = 0;
char buffer2[1024];
int pos2 = 0;
int pressEnter = 0; 

int checkInput() {
    return pressEnter;
}

void receiveEnter() {
    pressEnter = 1;
    // faltaria agregar un analizador de funcion para correrlas
}

char * getInput() {
    if (pressEnter) {
        if (getCurrentScreen() == 1) {
            return buffer1;
        } else {
            return buffer2;
        }
    } else {
        return 0;
    }
}

void buffDelete() {
    if (getCurrentScreen() == 1) {
        pos1--;
        buffer1[pos1] = 0;
    } else {
        pos2--;
        buffer2[pos2] = 0;
    }
}

void updateBuffer(char key) {
    if (getCurrentScreen() == 1) {
        if (pressEnter) {
            buffer1[0] = 0;
            pos1 = 0;
        }
        buffer1[pos1] = key;
        pos1++;
        buffer1[pos1] = 0;  // esto es porque el borrado lo defino como poner el primer bit en 0
                              // Necesito ir seteando el final cada vez que escribo una letra
    } else {
        if (pressEnter) {
            buffer2[0] = 0;
            pressEnter = 0;
            pos2 = 0;
        }
        buffer2[pos2] = key;
        pos2++;
        buffer2[pos2] = 0;
    }

    pressEnter = 0;
    writeLetter(key);
}