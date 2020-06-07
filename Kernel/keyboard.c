#include <keyboard.h>
#include <stdint.h>

extern uint8_t getKey();

#define KEYS 59
#define PRESSED 1
#define RELEASED 2
#define ERRROR -1

#define L_SHFT 0x2A
#define R_SHFT 0x36
#define CAPS_LCK 0x3A
#define CONTROL 0x1D
#define B_SPACE 0x0E
#define SPACE 0x39
#define ENTER 0x1C
#define ESC 27

#define IS_LETTER(c) (c >= 'a' && c <= 'z' ? 1 : 0)

static uint8_t action(uint8_t scanCode);

char buffer[1024];
int pos = 0;
char exitFlag = 0;

char * getBuffer(int screen) {
    return buffer;
}

void deleteBuff() {
    buffer[0] = 0;
    pos = 0;
}

int getExitFlag() {
    return exitFlag;
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

static uint8_t scanCode, currentAction, specialChars[] = {0, 0, 0}, capsLock = 0;

void bufferAdd(char key) {
    buffer[pos++] = key;
    buffer[pos] = 0;
}

void keyboard_handler(uint64_t * stackFrame) {
    uint8_t key = getKey();
    currentAction = action(key);
    if (action(key) == PRESSED) {
        switch (key) {
        case L_SHFT:
            specialChars[0] = 1;
            break;
        case R_SHFT:
            specialChars[1] = 1;
            break;
        case CONTROL:
            specialChars[2] = 1;
            break;
        case SPACE:
            bufferAdd(' ');
            break;
        case ENTER:
            bufferAdd('\n');
            break;
        case B_SPACE:
            bufferAdd(B_SPACE);
            break;
        
        default: 
            if (specialChars[2] == 1 && key == 0x1F) { // Control S para guardar un backup de los registros
                saveReg(stackFrame);
            } else {
                if (specialChars[0] == 1 || specialChars[1] == 1) {
                    bufferAdd(pressCodes[key][1]);
                } else {
                    bufferAdd(pressCodes[key][0]);
                }
            }
            break;
        }
    } else if (action(key) == RELEASED) {
        switch (key) { // el scancode de una tecla released es el scancode la tecla mas 0x80
            case L_SHFT + 0x80:
                specialChars[0] = 0;
                break;
            case R_SHFT + 0x80:
                specialChars[1] = 0;
                break;
            case CONTROL + 0x80:
                specialChars[2] = 0;
                break;
            default:
                break;
        }
    }
}

static uint8_t action(uint8_t scanCode) {
    if (scanCode >= 0x01 && scanCode <= 0x3A)
        return PRESSED;
    else if (scanCode >= 0x81 && scanCode <= 0xBA)
        return RELEASED;

    return ERRROR;
}