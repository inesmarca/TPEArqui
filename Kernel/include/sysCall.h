#ifndef __SYSCALL_H_
#define __SYSCALL_H_
#include <stdint.h>

void readKey(char * buf);

void writeString(const char * string);

void getPixelData(char * rgb, int x, int y);

void printPixel(int x, int y, int red, int green, int blue);

int getTemperature();

void getRecVec(uint64_t * buff);

#endif