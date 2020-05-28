#include <screenManager.h>

void printKey(int screen) {
    int * posX;
    int * posY;
    char ** buffer;
    int * dim_buffer;
    if (screen == 1) {
        posX = &pos1X;
        posY = &pos1Y;
        buffer = buffer1;
        dim_buffer = &dim1;
    } else {
        posX = &pos2X;
        posY = &pos2Y;
        buffer = buffer2;
        dim_buffer = &dim2;
    }
    read(0, &letter, 1);
    if (letter != 0) {
        blankBlock(*posX, *posY);
        if (letter == B_SPACE) {
            *posX -= LETTER_WIDTH;
            blankBlock(*posX, *posY);
            *dim_buffer--;
            *buffer[*dim_buffer] = 0;
        } else if (letter == '\n') {
            printf(*buffer);
        } else {
            writeLetter(letter, *posX, *posY);
            *posX += LETTER_WIDTH;
            *buffer[*dim_buffer] = letter;
            *dim_buffer++;
        }
        letter = 0;
        drawBlock(*posX, *posY);
    }
}

/*
void newLine(int screen) { // anda mal en el tope de la pantalla
    int * posX;
    int * posY;
    int max_pos = 0;
    if (screen == 1) {
        posX = &pos1X;
        posY = &pos1Y;
        buffer1[0] = 0;
        dim1 = 0;
    } else {
        max_pos = 400;
        posX = &pos2X;
        posY = &pos2Y;
        buffer2[0] = 0;
        dim2 = 0;
    }
    blankBlock(*posX, *posY);
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
    drawBlock(*posX, *posY);
} */