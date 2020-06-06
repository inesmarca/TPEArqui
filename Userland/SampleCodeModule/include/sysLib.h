#include <stdint.h>

extern void readKeyBuff(char * buf);

extern void writeScreen(const char * string);

extern void readPixel(char * rgb, int x, int y);

extern void writePixel(int x, int y, int red, int green, int blue);

extern int getExitFlag();

extern int getActiveScreen();

extern int getRTC(int x);

extern int getTemperature();

extern void getRegisters(uint64_t * buff);