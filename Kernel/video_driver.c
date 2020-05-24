#include <stdint.h>
#include <video_driver.h>
#include <font8x8_basic.h>

struct vbe_mode_info_structure {
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

static int currentScreen = 1;

unsigned int pos1X = 0;
unsigned int pos1Y = (HEIGHT / 2) - LINE_WIDTH - LETTER_HEIGHT;
unsigned int pos2X = 0;
unsigned int pos2Y = HEIGHT - LETTER_HEIGHT;

struct vbe_mode_info_structure * screen_info = 0x5C00;

void setXPosition(int screen, int value) {
	if (screen == 1) {
		pos1X = value;
	} else {
		pos2X = value;
	}
}

void setYPosition(int screen, int value) {
	if (screen == 1) {
		pos1Y = value;
	} else {
		pos2Y = value;
	}
}

char * getDataPosition(int x, int y) {
	return screen_info->framebuffer + (x + WIDTH * y) * 3;
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

void middleLine() {
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i, HEIGHT/2, 255, 255, 255);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i, HEIGHT/2 + 1, 255, 255, 255);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i, HEIGHT/2 - 1, 255, 255, 255);
	}
}

void drawLine(int line) {
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,line, 255, 255, 255);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,line + 1, 255, 255, 255);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,line - 1, 255, 255, 255);
	}
}

void changeScreen(int screen) {  
	if (screen == 1) {
		for (int i = 0; i < LETTER_WIDTH; i++) { // Setea el bloque del screen 1
			for (int j = HEIGHT/2 - LETTER_HEIGHT - LINE_WIDTH; j < HEIGHT/2 - LINE_WIDTH; j++) {
				writePixel(pos1X + i, j, 184, 184, 186);
			}
		}
		for (int i = 0; i < LETTER_WIDTH; i++) { // Borra el bloque del screen 2
			for (int j = HEIGHT - LETTER_HEIGHT; j < HEIGHT; j++) {
				writePixel(pos2X + i, j, 0, 0, 0);
			}
		}
	} else {
		for (int i = 0; i < LETTER_WIDTH; i++) { // Setea el bloque del screen 2
			for (int j = HEIGHT - LETTER_HEIGHT; j < HEIGHT; j++) {
				writePixel(pos2X + i, j, 184, 184, 186);
			}
		}
		for (int i = 0; i < LETTER_WIDTH; i++) {  // Borra el bloque del screen 1
			for (int j = HEIGHT/2 - LETTER_HEIGHT - LINE_WIDTH; j < HEIGHT/2 - LINE_WIDTH; j++) {
				writePixel(pos1X + i, j, 0, 0, 0);
			}
		}
	}
	currentScreen = screen;
}

int getCurrentScreen() {
	return currentScreen;
}

void delete() {
	int posX, posY;
	removeBlock();
	if (currentScreen == 1) { // Borrado en screen 1
		if (pos1X != 0) {
			pos1X -= 8;
			posX = pos1X;
			posY = pos1Y;
		}
	} else { // Borrado en screen 2
		if (pos2X != 0) { 
			pos2X -= 8;
			posX = pos2X;
			posY = pos2Y;
		}
	}
	int x,y;
    for (y=0; y < 8; y++) {  // Borra los bloques
        for (x=0; x < 8; x++) {
           writePixel(posX + x, posY + y, 0, 0, 0);
        }
    }
	changeScreen(currentScreen);
}

void removeBlock() {
	if (currentScreen == 1) {
		for (int i = 0; i < LETTER_WIDTH; i++) {
			for (int j = HEIGHT/2 - LETTER_HEIGHT - LINE_WIDTH; j < HEIGHT/2 - LINE_WIDTH; j++) {
				writePixel(pos1X + i, j, 0, 0, 0);
			}
		}
	} else {
		for (int i = 0; i < LETTER_WIDTH; i++) {
			for (int j = HEIGHT - LETTER_HEIGHT; j < HEIGHT; j++) {
				writePixel(pos2X + i, j, 0, 0, 0);
			}
		}
	}
}

void setSegmentBlank(int x_initial, int x_final, int y_initial, int y_final) {
	for (int i = y_initial; i <= y_final; i++) {
        for (int j = x_initial; j < x_final; j++) {
            writePixel(j, i, 0, 0, 0);
        }
    }
} 

void print(char * str) {
	for (int i = 0; str[i] != '\0'; i++) {
		writeLetter(str[i]);
	}
}

void newLine() {
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
                int redAux = getPositionRed(j,i);
                int greenAux = getPositionGreen(j,i);
                int blueAux = getPositionBlue(j,i);
                setSegmentBlank(j, WIDTH, i, i);
                writePixel(j, i, getPositionRed(j, i+LETTER_HEIGHT), getPositionGreen(j, i + LETTER_HEIGHT), getPositionBlue(j, i+LETTER_HEIGHT));
                writePixel(j, i + 16, redAux, greenAux, blueAux);
            }
        }
    }

    setSegmentBlank(0, WIDTH, SCREEN_HEIGHT + max_pos - LETTER_HEIGHT, SCREEN_HEIGHT + max_pos);
    changeScreen(getCurrentScreen());
}

void writeLetter(char key) {
	if (key == '\n') {
		newLine();
	} else {
		int posX, posY;

		if (currentScreen == 1) {
			posX = pos1X;
			posY = pos1Y;
		} else {
			posX = pos2X;
			posY = pos2Y;
		}

		char * bitmap = E_font[key];
		int x,y;
		int set1, set2;
		removeBlock();
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

		if (currentScreen == 1) {
			pos1X += LETTER_WIDTH;
			if (pos1X == WIDTH) {
				pos1Y -= LETTER_HEIGHT;
				pos1X += 0;
			}
		} else {
			pos2X += LETTER_WIDTH;
			if (pos2X == WIDTH) {
				posY += LETTER_HEIGHT;
				posX += 0;
			}
		}
		changeScreen(currentScreen);
	}
}