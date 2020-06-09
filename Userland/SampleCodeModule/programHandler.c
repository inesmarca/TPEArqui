#include <sysLib.h>
#include <programHandler.h>
#include <calculator.h>
#include <shell.h>
#include <programs.h>
#include <libC.h>

#define UP 1
#define DOWN 2

char user[30];
int exitFlag = 0;
static char buffer[DIM_BUFFER] = {0};

void exit() {
    exitFlag = 1;
}

int activeScreen;

void changeScreen(int screen) {
    activeScreen = screen;
    sysChangeScreen(screen);
}

char * getUser() {
    return user;
}

void initialize() {
    printf("Enter your username: ");
    scanf("%s", user);
}

void printUser() {
    changeLetterColor(0xFF00FF);
    printf("%s$: ", getUser());
    changeLetterColor(DEFAULT_LETTER_COLOR);
}

void programHandler() {
    changeScreen(DOWN);
    initialize();
    changeScreen(UP);
    initCalculator();
    changeScreen(DOWN);
    initShell();
    printBlock();
    while (!exitFlag) {
        readKeyBuff(buffer, WIDTH/8);
        for (int i = 0; buffer[i] != 0; i++) {
            if (buffer[i] == '\t') {
                if (activeScreen == UP) {
                    putChar(DELETE);
                    changeScreen(DOWN);
                    printBlock();
                } else {
                    putChar(DELETE);
                    changeScreen(UP);
                    printBlock();
                }
            } else {
                putChar(DELETE);
                if (activeScreen == UP) {
                    calculator(buffer[i]);
                } else {
                    shell(buffer[i]);
                }
                printBlock();
            }
            buffer[i] = 0;
        }
    }
}