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

int WIDTH = 1024;
int HEIGHT = 768;

char posX = 0;
char posY = 2;

struct vbe_mode_info_structure * screen_info = 0x5C00;

char * getDataPosition(int x, int y) {
	return screen_info->framebuffer + (x + WIDTH * y) * 3;
}

void writePixel(x, y) {
    char * pos = getDataPosition(x,y);
	pos[0] = 255;
	pos[1] = 255;
	pos[2] = 255;
}

void middleLine() {
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i, HEIGHT/2);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,HEIGHT/2 + 1);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,HEIGHT/2 - 1);
	}
}

void drawLine(int line) {
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,line);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,line + 1);
	}
	for (int i = 0; i < WIDTH; i++) {
		writePixel(i,line - 1);
	}
}

void pendingWrite(int screen) {  // usando el timer tick se puede hacer que titile
	if (screen == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT/2 - 16; j < HEIGHT/2; j++) {
				char * pos = getDataPosition(i,j);
				pos[0] = 184;
				pos[1] = 184;
				pos[2] = 186;
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			for (int j = HEIGHT - 16; j < HEIGHT; j++) {
				char * pos = getDataPosition(i,j);
				pos[0] = 184;
				pos[1] = 184;
				pos[2] = 186;
			}
		}
	}
}

void writeLetter() {
	char * bitmap = font8x16[11];
	int x,y;
    int set;
    for (y=15; y >= 0; y--) {
        for (x=7; x >= 0; x--) {
            set = bitmap[y] & 1 << x;
			if (set) {
				writePixel(y, x);
			}
        }
    }
}