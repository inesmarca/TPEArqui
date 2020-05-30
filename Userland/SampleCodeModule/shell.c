#include <shell.h>
#include <sysLib.h>

char inputBuffer = 0;

void shell() {
    while (!getExitFlag()) {
        while (getActiveScreen() == 1) {
            readKeyBuff(&inputBuffer);
            if (inputBuffer != 0) {
                printf(&inputBuffer);
                inputBuffer = 0;
            }
        }
        while (getActiveScreen() == 2) {

        }
    }
}