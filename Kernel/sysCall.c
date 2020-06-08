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

void writeString(const char * string, int letter_color, int background_color) {
    print(string, letter_color, background_color);
}

void getPixelData(int * rgb, int x, int y) {
    int screen = getCurrentScreen();
    if ((screen == 1 && y < SCREEN_HEIGHT) || (screen == 2 && y > HEIGHT - SCREEN_HEIGHT)) {
        *rgb = getPixelColor(x, y);
    }
}

void printPixel(int x, int y, int color) {
    if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0) {
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
