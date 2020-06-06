#include <stdint.h>

extern void readKeyBuff(char * buf);

extern void writeScreen(const char * string, int letter_color, int background_color);

extern void readPixel(char * rgb, int x, int y);

extern void writePixel(int x, int y, int color);

extern int getExitFlag();

extern int getActiveScreen();

extern int getRTC(int x);

extern int getTemperature();

extern void getRegisters(uint64_t * buff);