#include <consoleManager.h>
#include <videoDriver.h>

#define SCREEN_HEIGHT HEIGHT/2 - LETTER_HEIGHT
#define SCREEN1_START_POS 0
#define SCREEN2_START_POS SCREEN_HEIGHT + LETTER_HEIGHT
#define LINE_HEIGHT 3
#define LINE_START_POS SCREEN_HEIGHT + LETTER_HEIGHT/2 - LINE_HEIGHT/2
#define B_SPACE 0x0E

static char letter = 0;
static int pos1X = 0;
static int pos1Y = SCREEN_HEIGHT - LETTER_HEIGHT;
static int pos2X = 0;
static int pos2Y = HEIGHT - LETTER_HEIGHT;

static int currentScreen = 1;

void changeScreen(int screen) { currentScreen = screen; }

int getCurrentScreen() { return currentScreen; }

void print(const char * string) {
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
            newLine();
        } else if (string[i] == B_SPACE) {
            delete();
        } else {
            writeLetter(string[i], *posX, *posY);
            *posX += LETTER_WIDTH;        
        }
    }
}

void delete() {
    int * posX;
    int * posY;
    if (getCurrentScreen() == 1) {
        posX = &pos1X;
        posY = &pos1Y;
    } else {
        posX = &pos2X;
        posY = &pos2Y;
    }

    *posX -= LETTER_WIDTH;
    setSegmentBlank(*posX, *posX + LETTER_WIDTH, *posY, *posY + LETTER_HEIGHT);
}

void newLine() {
    int * posX;
    int max_pos = 0;
    if (getCurrentScreen() == 1) {
        posX = &pos1X;
    } else {
        max_pos = 400;
        posX = &pos2X;
    }
    *posX = 0;

    for (int y = 0 + max_pos; y < max_pos + SCREEN_HEIGHT - LETTER_HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (!positionEmpty(x,y+LETTER_HEIGHT)) {
                int redAux = getPositionRed(x,y);
                int greenAux = getPositionGreen(x,y);
                int blueAux = getPositionBlue(x,y);
                setSegmentBlank(x, WIDTH, y, y);
                writePixel(x, y, getPositionRed(x, y+LETTER_HEIGHT), getPositionGreen(x, y + LETTER_HEIGHT), getPositionBlue(x, y+LETTER_HEIGHT));
                writePixel(x, y + LETTER_HEIGHT, redAux, greenAux, blueAux);
            }
        }
    }
}

void middleLine() {
    for (int i = 0; i < LINE_HEIGHT; i++) {
        drawLine(LINE_START_POS + i);
    }
}