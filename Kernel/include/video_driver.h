#define WIDTH 1024
#define HEIGHT 768
#define LINE_WIDTH 3
#define LETTER_WIDTH 8
#define LETTER_HEIGHT 16

void writePixel(int x, int y, int red, int green, int blue);

void setYPosition(int screen, int value);

void setXPosition(int screen, int value);

void setSegmentBlank(int x_initial, int x_final, int y_initial, int y_final);

void middleLine();

void changeScreen(int screen);

int getCurrentScreen();

void drawLine(int pos);

void writeLetter(char key);

void delete();

char positionEmpty(int x, int y);

char getPositionRed(int x, int y);

char getPositionBlue(int x, int y);

char getPositionGreen(int x, int y);

void removeBlock();

void print(char * str);