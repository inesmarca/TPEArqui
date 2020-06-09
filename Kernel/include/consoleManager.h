#ifndef __CONSOLE_MANAGER_H_
#define __CONSOLE_MANAGER_H_

#define SCREEN1_START_POS 4
#define SCREEN1_END_POS 372
#define SCREEN2_START_POS 382
#define SCREEN2_END_POS 766
#define SCREEN1_HEIGHT SCREEN1_END_POS - SCREEN1_START_POS
#define SCREEN2_HEIGHT SCREEN2_END_POS - SCREEN2_START_POS
#define BACKGROUND_COLOR 0x000000
#define LETTER_COLOR 0xFFFFFF

int getCurrentScreen();

void changeScreen(int screen);

void print(const char * string, int letter_color, int background_color);

void delete(int background_color);

void middleLine();

void newLine(int background_color);

void clear();

void changeCursor(int screen, int x, int y);

#endif