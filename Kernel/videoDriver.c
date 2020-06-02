#include <videoDriver.h>
#include <font8x16.h>
#include <stdint.h>

struct infoStructure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be LETTER_HEIGHT KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

struct infoStructure * screenInfo = 0x5C00;

char * getDataPosition(int x, int y) {
	return screenInfo->framebuffer + (x + WIDTH * y) * 3;
}

char positionEmpty(int x, int y) {
	char * pos = getDataPosition(x, y);
	return pos[0] == 0 && pos[1] == 0 && pos[2] == 0;
}

char getPositionRed(int x, int y) {
	char * pos = getDataPosition(x, y);
	return pos[2];
}

char getPositionGreen(int x, int y) {
	char * pos = getDataPosition(x, y);
	return pos[1];
}

char getPositionBlue(int x, int y) {
	char * pos = getDataPosition(x, y);
	return pos[0];
}

void writePixel(int x, int y,  int red, int green, int blue) {
    char * pos = getDataPosition(x,y);
	pos[0] = red;
	pos[1] = green;
	pos[2] = blue;
}

void writeLetter(char key, int posX, int posY) {
	char * bitmap = font8x16[key];
	int x,y;
	int set1, set2;
	for (y=0; y < LETTER_WIDTH; y++) {
		for (x=0; x < LETTER_WIDTH; x++) {
			set1 = bitmap[x] & 1 << y;
			set2 = bitmap[x + LETTER_WIDTH] & 1 << y;
			if (set1) {
				writePixel(posX + x, posY + y, 255, 255, 255);
			}
			if (set2) {
				writePixel(posX + x, posY + y + LETTER_WIDTH, 255, 255, 255);
			}
		}
	}
}

void drawLine(int y) {
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,y, 255, 255, 255);
	}
}

void setSegmentBlank(int x_initial, int x_final, int y_initial, int y_final) {
	for (int i = y_initial; i <= y_final; i++) {
        for (int j = x_initial; j < x_final; j++) {
            writePixel(j, i, 0, 0, 0);
        }
    }
} 