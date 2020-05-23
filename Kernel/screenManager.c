#include <keyboard.h>
#include <video_driver.h>
#include <screenManager.h>
#include <calculator.h>

#define SCREEN_HEIGHT (HEIGHT - LINE_WIDTH) / 2

char input1[1024];
int pos1 = 0;
char input2[1024];
int pos2 = 0;

void enterInput() {
    int screen = getCurrentScreen();
    if (screen == 1) {
        if (input1[0] != '\0') {
            updateScreen();
        }
        runCalc(input1, pos1); // Funcion que corre la screen1
        input1[0] = '\0';
        pos1 = 0;
    } else {
        if (input2[0] != '\0') {
            updateScreen();
        }
        runInput(input2, pos2); // Funcion que corre la screen2 (yo lo programaria todo en otro archivo)
        input2[0] = '\0';
        pos2 = 0;
    }
}

void runInput(char * str, int dim) {}

void updateScreen() {  // Corregir que si input esta empty que no haga nada y esta haciendo algo raro cuando solo haces input de numeros
    removeBlock();
    int max_pos = 0;
    if (getCurrentScreen() == 2) {
        max_pos = SCREEN_HEIGHT + LINE_WIDTH;
        setXPosition(2, 0);
    } else {
        setXPosition(1, 0);
    }

    for (int i = 0 + max_pos; i < SCREEN_HEIGHT - LETTER_HEIGHT + max_pos; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (!positionEmpty(j,i+LETTER_HEIGHT)) {
                setSegmentBlank(j, WIDTH, i, i);
                writePixel(j, i, getPositionRed(j, i+LETTER_HEIGHT), getPositionGreen(j, i + LETTER_HEIGHT), getPositionBlue(j, i+LETTER_HEIGHT));
            }
        }
    }

    setSegmentBlank(0, WIDTH, SCREEN_HEIGHT + max_pos - LETTER_HEIGHT, SCREEN_HEIGHT + max_pos);
    changeScreen(getCurrentScreen());
}

void getInput(char key) {
    if (getCurrentScreen() == 1) {
        input1[pos1] = key;
        pos1++;
        input1[pos1] = '\0';  // esto es porque el borrado lo defino como poner el primer bit en 0
                              // Necesito ir seteando el final cada vez que escribo una letra
    } else {
        input2[pos2] = key;
        pos2++;
        input2[pos2] = '\0';
    }

    writeLetter(key);
}