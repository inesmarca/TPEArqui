#ifndef __SYS_LIB_H_
#define __SYS_LIB_H_

#include <stdint.h>

extern void readKeyBuff(char * buf, int cant);

extern void writeScreen(const char * string, int letter_color, int background_color);

extern void readPixel(char * rgb, int x, int y);

extern void writePixel(int x, int y, int color);

extern int getExitFlag();

extern void sysChangeScreen(int screen);

extern int getRTC(int x);

extern int getTemperature();

extern void clear();

extern void getRegisters(uint64_t * buff);

#endif