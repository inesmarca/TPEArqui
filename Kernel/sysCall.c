#include <sysCall.h>

size_t write(int fd, const char *buf, size_t count) {
    print(buf);
}