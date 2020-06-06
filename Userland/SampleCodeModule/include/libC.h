#include <stdint.h>

char * strcpy(char * destination,const char * source);

int strcmp(char * s1, char * s2);

//int scanf(char * s, void * pointer);
int scanf(const char *format, ...);

void putChar(char str);

char getChar();

void printf(const char * format,...);

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

void printTime();

void printTemperature();