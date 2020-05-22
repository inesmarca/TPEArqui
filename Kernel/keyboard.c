#include <keyboard.h>
#include <video_driver.h>
#include <stdint.h>

extern uint8_t getKey();

static unsigned long pos = 0;

void keyboard_handler() {
    int key = getKey();
    writeLetter();
}