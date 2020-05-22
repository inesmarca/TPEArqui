#include <stdint.h>
#include <video_driver.h>
#include <font8x8_basic.h>

#define WIDTH 1024
#define HEIGHT 768

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
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
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
unsigned int pos1Y = HEIGHT / 2 - 2 - 16;

unsigned int pos2X = 0;
unsigned int pos2Y = HEIGHT - 16;

struct vbe_mode_info_structure * screen_info = 0x5C00;

char * getDataPosition(int x, int y) {
	return screen_info->framebuffer + (x + WIDTH * y) * 3;
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
		writePixel(i,HEIGHT/2 + 1, 255, 255, 255);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,HEIGHT/2 - 1, 255, 255, 255);
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
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT/2 - 16; j < HEIGHT/2; j++) {
				writePixel(pos1X + i, j, 184, 184, 186);
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT - 16; j < HEIGHT; j++) {
				writePixel(pos2X + i, j, 0, 0, 0);
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT - 16; j < HEIGHT; j++) {
				writePixel(pos2X + i, j, 184, 184, 186);
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT/2 - 16; j < HEIGHT/2; j++) {
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
	if (currentScreen == 1) {
		if (pos1X != 0) {
			pos1X -= 8;
			posX = pos1X;
			posY = pos1Y;
		}
	} else {
		if (pos2X != 0) {
			pos2X -= 8;
			posX = pos2X;
			posY = pos2Y;
		}
	}
	int x,y;
    for (y=0; y < 8; y++) {
        for (x=0; x < 8; x++) {
           writePixel(posX + x, posY + y, 0, 0, 0);
        }
    }
	changeScreen(currentScreen);
}

void removeBlock() {
	if (currentScreen == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT/2 - 16; j < HEIGHT/2; j++) {
				writePixel(pos1X + i, j, 0, 0, 0);
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT - 16; j < HEIGHT; j++) {
				writePixel(pos2X + i, j, 0, 0, 0);
			}
		}
	}
}

void writeLetter(char key) {
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
    int set;
	removeBlock();
    for (y=0; y < 8; y++) {
        for (x=0; x < 8; x++) {
            set = bitmap[x] & 1 << y;
			if (set) {
				writePixel(posX + x, posY + y, 255, 255, 255);
			}
        }
    }
	for (y = 0; y < 8; y++) {
		for (x = 8; x < 16; x++) {
			set = bitmap[x] & 1 << y;
			if (set) {
				writePixel(posX + x - 8, posY + y + 8, 255, 255, 255);
			}
		}
	}

	if (currentScreen == 1) {
		pos1X += 8;
		if (pos1X == 1024) {
			pos1Y -= 8;
			pos1X += 0;
		}
	} else {
		pos2X += 8;
		if (pos2X == 1024) {
			posY += 8;
			posX += 0;
		}
	}
	changeScreen(currentScreen);
}