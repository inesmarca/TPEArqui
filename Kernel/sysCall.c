#include <sysCall.h>
#include <screenManager.h>

// si el rdi es 0 entoces hace print en currentScreen, si es 1 hace print en screen1, si es 2 hace print en screen2
size_t write(int screen, const char *buf, size_t count) {
    print(screen, buf);
}

size_t read(int screen, char *buf, size_t count) {
    char * input = getInput(screen);
    for (int i = 0; input[i] != 0; i++) {
        buf[i] = input[i];
    }
}