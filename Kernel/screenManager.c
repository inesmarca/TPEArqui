#include <keyboard.h>
#include <video_driver.h>
#include <screenManager.h>

#define SCREEN_HEIGHT (HEIGHT - LINE_WIDTH) / 2

char * input1[1024];
char * input2[1024];

void updateScreen() {  // Corregir que si input esta empty que no haga nada y esta haciendo algo raro cuando solo haces input de numeros
    removeBlock();
    int max_pos = 0;
    if (getCurrentScreen() == 2) {
        max_pos = SCREEN_HEIGHT + LINE_WIDTH;
        setXPosition(2, 0);
    } else {
        setXPosition(1, 0);
    }

    for (int i = 0 + max_pos; i < SCREEN_HEIGHT - LETTER_HEIGHT + max_pos; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (!positionEmpty(j,i+LETTER_HEIGHT)) {
                setSegmentBlank(j, WIDTH, i, i);
                writePixel(j, i, getPositionRed(j, i+LETTER_HEIGHT), getPositionGreen(j, i + LETTER_HEIGHT), getPositionBlue(j, i+LETTER_HEIGHT));
            }
        }
    }

    setSegmentBlank(0, WIDTH, SCREEN_HEIGHT + max_pos - LETTER_HEIGHT, SCREEN_HEIGHT + max_pos);

    changeScreen(getCurrentScreen());
}