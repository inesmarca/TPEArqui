#define SCREEN_HEIGHT 368
#define WIDTH 1024
#define HEIGHT 768
#define LETTER_WIDTH 8
#define LETTER_HEIGHT 16
#define B_SPACE 0x0E

static char letter = 0;
static int pos1X = 0;
static int pos1Y = SCREEN_HEIGHT - LETTER_HEIGHT;
static int pos2X = 0;
static int pos2Y = SCREEN_HEIGHT - LETTER_HEIGHT;
static char buffer1[1024];
static int dim1;
static char buffer2[1024];
static int dim2;

extern int getExitFlag();
extern int getScreen();

void getKey(int screen);

void printKey(int screen);

void newLine();