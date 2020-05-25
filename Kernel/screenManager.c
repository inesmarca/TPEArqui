#include <video_driver.h>
#include <screenManager.h>
#include <libC.h>
#include <func.h>

// DEFINES
#define SCREEN_HEIGHT HEIGHT/2 - LETTER_HEIGHT
#define SCREEN1_START_POS 0
#define SCREEN2_START_POS SCREEN_HEIGHT + LETTER_HEIGHT
#define LINE_HEIGHT 3
#define LINE_START_POS SCREEN_HEIGHT + LETTER_HEIGHT/2 - LINE_HEIGHT/2

// Variables de input
char buffer1[WIDTH];
int pos_buffer1 = 0;
char buffer2[WIDTH];
int pos_buffer2 = 0;

// Variables de pantalla
int pos1X = 0;
int pos1Y = SCREEN_HEIGHT - LETTER_HEIGHT;
int pos2X = 0;
int pos2Y = HEIGHT - LETTER_HEIGHT;

int pressEnter = 0; 
char currentScreen = 1;

int checkEnter() {
    return pressEnter;
}

void gotEnter() {
    pressEnter = 1;
}

void changeScreen(char screen) {
    removeBlock();
    currentScreen = screen;
    drawBlock();
}

char * getInput(int screen) {
    if (screen == 1 || (screen == 0 && currentScreen == 1)) {
        return buffer1;
    } else {
        return buffer2;
    }
}

void buffDelete() {
    if (currentScreen == 1) {
        pos_buffer1--;
        buffer1[pos_buffer1] = 0;
    } else {
        pos_buffer2--;
        buffer2[pos_buffer2] = 0;
    }
}

void print(int screen, char * string) {
    removeBlock();
    int posX, posY;
    if (screen == 1 || (screen == 0 && currentScreen == 1)) {
        posX = pos1X;
        posY = pos1Y;
    } else {
        posX = pos2X;
        posY = pos2Y;
    }

    for (int i = 0; string[i] != 0; i++) {
        writeLetter(string[i], posX, posY);
        posX += LETTER_WIDTH;
    }
    if (screen == 1) {
        pos1X = posX;
    } else {
        pos2X = posX;
    }
    drawBlock();
}

void middleLine() {
    for (int i = 0; i < LINE_HEIGHT; i++) {
        drawLine(LINE_START_POS + i);
    }
}

void removeBlock() {
    int * posX;
    int * posY;
    if (currentScreen == 1) {
        posX = &pos1X;
        posY = &pos1Y;
    } else {
        posX = &pos2X;
        posY = &pos2Y;
    }
    setSegmentBlank(*posX, *posX + LETTER_WIDTH, *posY, *posY + LETTER_HEIGHT);
}

void drawBlock() {
    int * posX;
    int * posY;
    if (currentScreen == 1) {
        posX = &pos1X;
        posY = &pos1Y;
    } else {
        posX = &pos2X;
        posY = &pos2Y;
    }
    for (int i = *posX; i < *posX + LETTER_WIDTH; i++) {
		for (int j = *posY; j < *posY + LETTER_HEIGHT; j++) {
			writePixel(i, j, 184, 184, 186);
		}
	}
}

void updateBuffer(char key) {
    if (currentScreen == 1) {
        if (pressEnter) {
            buffer1[0] = 0;
            pos_buffer1 = 0;
        }
        buffer1[pos_buffer1] = key;
        pos_buffer1++;
        buffer1[pos_buffer1] = 0;  // esto es porque el borrado lo defino como poner el primer bit en 0
                                    // Necesito ir seteando el final cada vez que escribo una letra
    } else {
        if (pressEnter) {
            buffer2[0] = 0;
            pressEnter = 0;
            pos_buffer2 = 0;
        }
        buffer2[pos_buffer2] = key;
        pos_buffer2++;
        buffer2[pos_buffer2] = 0;
    }

    pressEnter = 0;
    print(currentScreen, &key);
}

void newLine() { // anda mal en el tope de la pantalla
    removeBlock();
    int max_pos = 0;
    if (currentScreen == 2) {
        max_pos = 400;  // es HEIGHT - SCREEN_HEIGHT pero nose porque no me lo lee 
        pos2X = 0;
    } else {
        pos1X = 0;
    }

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
    drawBlock();
}

void delete() {
    buffDelete();
    int * posX;
    if (currentScreen == 1) {
        posX = &pos1X;
    } else {
        posX = &pos2X;
    }
	removeBlock();
    *posX -= LETTER_WIDTH;
    drawBlock();
}