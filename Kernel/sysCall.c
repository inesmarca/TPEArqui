#include <sysCall.h>
#include <screenManager.h>

size_t write(int fd, const char *buf, size_t count) {
    print(buf);
}

size_t read(int fd, char *buf, size_t count) {
    char * input = getInput();
    for (int i = 0; input[i] != 0; i++) {
        buf[i] = input[i];
    }
}