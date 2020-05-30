#include <shell.h>
#include <sysLib.h>
#include <libC.h>

extern char * cpuVendor();
extern char * cpuModel();
char inputBuffer = 0;

void shell() {
    printf(cpuVendor());
    printf(cpuModel());
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