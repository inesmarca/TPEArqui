#include <keyboard.h>
#include <video_driver.h>
#include <stdint.h>

extern uint8_t getKey();

#define KEYS 59
#define PRESSED 1
#define RELEASED 2
#define ERRROR -1

#define L_SHFT 0x2A
#define R_SHFT 0x36
#define B_SPACE 0x0E
#define SPACE 0x39
#define CAPS_LCK 0x3A
#define ENTER 0x1C
#define CONTROL 0x1D

#define IS_LETTER(c) (c >= 'a' && c <= 'z' ? 1 : 0)

#define ABS(num) (num >= 0 ? num : num * -1)

static uint8_t action(uint8_t scanCode);

static const char pressCodes[KEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'},
    {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('},
    {'0', ')'}, {'-', '_'}, {'=', '+'}, {0, 0}, {0, 0}, {'q', 'Q'}, 
    {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, 
    {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, 
    {']', '}'}, {0, 0}, {0, 0}, {'a', 'A'}, {'s', 'S'}, 
    {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'},
    {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'},
    {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, 
    {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, 
    {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

static uint8_t scanCode, currentAction, specialChars[] = {0, 0, 0}, capsLock = 0;

void keyboard_handler() {
    int key = getKey();
    if (action(key) == PRESSED) {
        switch (key)
        {
        case L_SHFT:
            specialChars[0] = 1;
            break;
        case R_SHFT:
            specialChars[1] = 1;
            break;
        case CONTROL:
            specialChars[2] = 1;
            break;
        case ENTER:
            //runInput();
            break;
        case B_SPACE:
            //deleteChar();
            break;
        case SPACE:
            //writeLetter(' ');
            break;
        
        default:
            if (specialChars[2] == 1 && key == 0x03) {
                changeScreen(2);
            } else if (specialChars[2] == 1 && key == 0x02) {
                changeScreen(1);
            }
            break;
        }
    } else if (action(key) == RELEASED) {
        specialChars[0] = specialChars[1] = specialChars[2] = 0;
    }
}

static uint8_t action(uint8_t scanCode) {
    if (scanCode >= 0x01 && scanCode <= 0x3A)
        return PRESSED;
    else if (scanCode >= 0x81 && scanCode <= 0xBA)
        return RELEASED;

    return ERRROR;
}