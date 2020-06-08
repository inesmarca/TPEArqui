#ifndef __CONSOLE_MANAGER_H_
#define __CONSOLE_MANAGER_H_

#define SCREEN_HEIGHT 368
#define BACKGROUND_COLOR 0x000000
#define LETTER_COLOR 0xFFFFFF

int getCurrentScreen();

void changeScreen(int screen);

void print(const char * string, int letter_color, int background_color);

void delete(int background_color);

void middleLine();

void newLine(int background_color);

void clear();

#endif