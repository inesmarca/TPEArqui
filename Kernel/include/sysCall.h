#include <stdlib.h>
#include <video_driver.h>

size_t read(int fd, char *buf, size_t count);

size_t write(int fd, const char *buf, size_t count);

void printPixel(int x, int y,  int red, int green, int blue);