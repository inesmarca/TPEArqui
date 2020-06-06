#include <keyboard.h>
#include <consoleManager.h>
#include <videoDriver.h>
#include <temperature.h>
#include <stdint.h>

void readKey(char * buf) {
    char * input = getBuffer();
    int i;
    for (i = 0; input[i] != 0; i++) {
        buf[i] = input[i];
    }
    buf[i] = input[i];
    deleteBuff();
}

void writeString(const char * string) {
    print(string);
}

void getPixelData(char * rgb, int x, int y) {
    int screen = getCurrentScreen();
    if ((screen == 1 && y < SCREEN_HEIGHT) || (screen == 2 && y > HEIGHT - SCREEN_HEIGHT)) {
        rgb[0] = getPositionRed(x, y);
        rgb[1] = getPositionGreen(x, y);
        rgb[2] = getPositionBlue(x, y);
    }
}

void printPixel(int x, int y, int red, int green, int blue) {
    writePixel(x, y, red, green, blue);
}

int getTemperature(){
    return getTemp();
}

void getRegVec(uint64_t * buff) {
    uint64_t * memory = getVec();
    for (int i = 0; i != 18; i++) {
        buff[i] = memory[i];
    }
}
