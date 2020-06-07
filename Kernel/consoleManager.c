#include <consoleManager.h>
#include <videoDriver.h>

#define SCREEN1_START_POS 4
#define SCREEN1_END_POS 371
#define SCREEN2_START_POS 382
#define SCREEN2_END_POS 765
#define LINE_START_POS 375
#define LINE_HEIGHT 3
#define B_SPACE 0x0E

static char letter = 0;
static int pos1X = 0;
static int pos1Y = SCREEN1_END_POS - LETTER_HEIGHT + 1;
static int pos2X = 0;
static int pos2Y = SCREEN2_END_POS - LETTER_HEIGHT + 1;

static int currentScreen = 1;

void changeScreen(int screen) { 
    if (screen == 1 || screen == 2) {
        currentScreen = screen; 
    }
}

int getCurrentScreen() { return currentScreen; }

void print(const char * string, int letter_color, int background_color) {
    int * posX;
    int * posY;
    if (getCurrentScreen() == 1) {
        posX = &pos1X;
        posY = &pos1Y;
    } else {
        posX = &pos2X;
        posY = &pos2Y;
    }

    for (int i = 0; string[i] != 0; i++) {
        if (string[i] == '\n') {
            newLine(background_color);
        } else if (string[i] == B_SPACE) {
            delete(background_color);
        } else {
            writeLetter(string[i], *posX, *posY, letter_color, background_color);
            *posX += LETTER_WIDTH;        
        }
    }
}

void delete(int background_color) {
    int * posX;
    int * posY;
    if (getCurrentScreen() == 1) {
        posX = &pos1X;
        posY = &pos1Y;
    } else {
        posX = &pos2X;
        posY = &pos2Y;
    }
    if (*posX != 0) {
        *posX -= LETTER_WIDTH;
        setSegmentBlank(*posX, *posX + LETTER_WIDTH, *posY, *posY + LETTER_HEIGHT, background_color);
    }
}

void newLine(int background_color) {
    int * posX;
    int top_pos;
    int bottom_pos;
    if (getCurrentScreen() == 1) {
        posX = &pos1X;
        top_pos = SCREEN1_START_POS;
        bottom_pos = SCREEN1_END_POS;
    } else {
        posX = &pos2X;
        top_pos = SCREEN2_START_POS;
        bottom_pos = SCREEN2_END_POS;
    }
    *posX = 0;
    setSegmentBlank(0, WIDTH, top_pos, top_pos + LETTER_HEIGHT, background_color);
    for (int y = top_pos; y < bottom_pos - LETTER_HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int color = getPixelColor(x, y);
            writePixel(x, y, getPixelColor(x, y + LETTER_HEIGHT));
            writePixel(x, y + LETTER_HEIGHT, color);
        }
    }
}

void middleLine() {
    for (int i = 0; i < LINE_HEIGHT; i++) {
        drawLine(LINE_START_POS + i, 0x62FFCC);
    }
}