#include <keyboard.h>
#include <stdint.h>
#include <registers.h>

extern uint8_t getKey();

#define KEYS 59
#define PRESSED 1
#define RELEASED 2
#define ERRROR -1

#define L_SHIFT 0x2A
#define R_SHIFT 0x36
#define CAPS_LCK 0x3A
#define CTRL 0x1D
#define DELETE 0x0E
#define SPACE 0x39
#define ENTER 0x1C
#define ESC 27

static uint8_t keyState(uint8_t scanCode);

char buffer[1024];
int pos = 0;

char * getBuffer(int screen) {
    return buffer;
}

void deleteBuff() {
    buffer[0] = 0;
    pos = 0;
}

// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html pagina con los scancodes
static const char pressCodes[KEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'},
    {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('},
    {'0', ')'}, {'-', '_'}, {'=', '+'}, {0, 0}, {'\t','\t'}, {'q', 'Q'}, 
    {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, 
    {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, 
    {']', '}'}, {0, 0}, {0, 0}, {'a', 'A'}, {'s', 'S'}, 
    {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'},
    {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'},
    {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, 
    {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, 
    {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

static int currentkeyState = 0;
static int left_shift = 0;
static int right_shift = 0;
// static int capsLock = 0;
static int control = 0;

void bufferAdd(char key) {
    buffer[pos++] = key;
    buffer[pos] = 0;
}

void keyboard_handler(uint64_t * stackFrame) {
    uint8_t key = getKey();
    currentkeyState = keyState(key);
    if (currentkeyState == PRESSED) {
        switch (key) {
        case L_SHIFT:
            left_shift = 1;
            break;
        case R_SHIFT:
            right_shift = 1;
            break;
        case CTRL:
            control = 1;
            break;
        case SPACE:
            bufferAdd(' ');
            break;
        case ENTER:
            bufferAdd('\n');
            break;
        case DELETE:
            bufferAdd(DELETE);
            break;
        
        default: 
            if (control == 1 && key == 0x1F) { // Control S para guardar un backup de los registros
                saveReg(stackFrame);
            } else {
                if (left_shift == 1 || right_shift == 1) {
                    bufferAdd(pressCodes[key][1]);
                } else {
                    bufferAdd(pressCodes[key][0]);
                }
            }
            break;
        }
    } else if (keyState(key) == RELEASED) {
        switch (key) { // el scancode de una tecla released es el scancode la tecla mas 0x80
            case L_SHIFT + 0x80:
                left_shift = 0;
                break;
            case R_SHIFT + 0x80:
                right_shift = 0;
                break;
            case CTRL + 0x80:
                control = 0;
                break;
            default:
                break;
        }
    }
}

static uint8_t keyState(uint8_t scanCode) {
    if (scanCode >= 0x01 && scanCode <= 0x3A)
        return PRESSED;
    else if (scanCode >= 0x81 && scanCode <= 0xBA)
        return RELEASED;

    return ERRROR;
}