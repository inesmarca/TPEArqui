#define WIDTH 1024
#define HEIGHT 768
#define LETTER_WIDTH 8
#define LETTER_HEIGHT 16

char * getDataPosition(int x, int y);

char positionEmpty(int x, int y);

char getPositionRed(int x, int y);

char getPositionGreen(int x, int y);

char getPositionBlue(int x, int y);

void writePixel(int x, int y, int red, int green, int blue);

void drawLine(int y);

void setSegmentBlank(int x_initial, int x_final, int y_initial, int y_final);

void writeLetter(char key, int posX, int posY);