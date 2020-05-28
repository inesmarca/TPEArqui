#include <sysCall.h>
#include <screenManager.h>
#include <keyboard.h>

#define SCREEN_HEIGHT 368

// si el rdi es 0 entoces hace print en currentScreen, si es 1 hace print en screen1, si es 2 hace print en screen2
size_t write(int screen, const char *buf, size_t count) {
    print(screen, buf);
    newLine();
}

size_t read(int screen, char *buf, size_t count) {
    char * input = getBuffer(screen);
    int i;
    for (i = 0; input[i] != 0; i++) {
        buf[i] = input[i];
    }
    buf[i] = input[i];
    deleteBuff();
}

void printPixel(int x, int y,  int red, int green, int blue) {
    int plusY = 0;
    if (getCurrentScreen() == 2) {
        plusY = HEIGHT - 368;
    }
    writePixel(x, y + plusY, red, green, blue);
}