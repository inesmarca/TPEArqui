#include <sysLib.h>

#define UP 1
#define DOWN 2


int exitFlag = 0;

void exit() {
    exitFlag = 1;
}

int activeScreen;

void changeScreen(int screen) {
    activeScreen = screen;
    sysChangeScreen(screen);
}

void programHandler() {
    changeScreen(DOWN);
    while (!exitFlag) {
        if (activeScreen == UP) {
            calculator();
            changeScreen(DOWN);
        } else {
            shell();
            changeScreen(UP);
        }
    }
}