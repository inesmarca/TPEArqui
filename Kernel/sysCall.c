#include <keyboard.h>
#include <consoleManager.h>
#include <videoDriver.h>
#include <temperature.h>
#include <stdint.h>
#include <registers.h>

void readKey(char * buf, int cant) {
    char * input = getBuffer();
    int i;
    for (i = 0; input[i] != 0 && i < cant; i++) {
        buf[i] = input[i];
    }
    deleteBuff();
}

void writeString(const char * string, unsigned int letter_color, unsigned int background_color) {
    print(string, letter_color, background_color);
}

void getPixelData(int * rgb, int x, int y) {
    int screen = getCurrentScreen();
    if (((screen == 1 && y >= 0 && y < SCREEN1_HEIGHT) || (screen == 2 && y >= 0 && y < SCREEN2_HEIGHT)) && x >= 0 && x < WIDTH) {
        *rgb = getPixelColor(x, y);
    }
}

void printPixel(int x, int y, int color) {
    int screen = getCurrentScreen();
    if (((screen == 1 && y >= 0 && y < SCREEN1_HEIGHT) || (screen == 2 && y >= 0 && y < SCREEN2_HEIGHT)) && x >= 0 && x < WIDTH) {
        writePixel(x, y, color);
    }
}

int getTemperature(){
    return getTemp();
}

void getRegVec(uint64_t * buff) {
    uint64_t * memory = getVec();
    for (int i = 0; i != 19; i++) {
        buff[i] = memory[i];
    }
}

void sysClear() {
    clear(getCurrentScreen());
}

void setCursor(int x, int y) {
    int screen = getCurrentScreen();
    if (((screen == 1 && y >= LETTER_HEIGHT && y < SCREEN1_HEIGHT) || (screen == 2 && y >= LETTER_HEIGHT && y < SCREEN2_HEIGHT)) && x >= 0 && x < WIDTH - LETTER_WIDTH) {
        if (screen == 1) {
            changeCursor(screen, x, y + SCREEN1_START_POS);
        } else {
            changeCursor(screen, x, y + SCREEN2_START_POS);
        }
    }
}
