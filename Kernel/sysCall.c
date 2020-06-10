#include <keyboard.h>
#include <consoleManager.h>
#include <videoDriver.h>
#include <temperature.h>
#include <stdint.h>
#include <registers.h>

// Funcion de syscall que retorna el buffer de keys leidas
void readKey(char * buf, int cant) {
    char * input = getBuffer();
    int i;
    for (i = 0; input[i] != 0 && i < cant; i++) {
        buf[i] = input[i];
    }
    deleteBuff();
}

// escribe en pantalla dicho string con los colores especificados en la pantalla activa
void writeString(const char * string, unsigned int letter_color, unsigned int background_color) {
    print(string, letter_color, background_color);
}

// retorna un numero hexadecimal del color de dicho pixel
int getPixelData(int x, int y) {
    int screen = getCurrentScreen();
    if ((y >= 0 && y < SCREEN_HEIGHT) && x >= 0 && x < WIDTH) {
        int res;
        if (screen == 1) res = getPixelColor(x, y);
        else res = getPixelColor(x, y + SCREEN2_START_POS);
        return res;
    }
}

// dibuja en pantalla dicho pixel con el color recivido en base a las coordenads relativas de la pantalla activa
void printPixel(int x, int y, int color) {
    int screen = getCurrentScreen();
    if ( y >= 0 && y < SCREEN_HEIGHT && x >= 0 && x < WIDTH) {
        if (screen == 1) writePixel(x, y, color);
        else writePixel(x, y + SCREEN2_START_POS, color);
    }
}

// retorna el valor de la temperatura
int getTemperature(){
    return getTemp();
}


// retorna el vector de registros que fueron gurdados al apretar CTRL S
void getRegVec(uint64_t * buff) {
    uint64_t * memory = getVec();
    for (int i = 0; i != 19; i++) {
        buff[i] = memory[i];
    }
}

// limpia la pantalla activa
void sysClear() {
    clear(getCurrentScreen());
}

// cambia de posicion el cursor de escritura dependiendo de la pantalla activa
void setCursor(int x, int y) {
    int screen = getCurrentScreen();
    if ((y >= LETTER_HEIGHT && y < SCREEN_HEIGHT) && x >= 0 && x < WIDTH - LETTER_WIDTH) {
        if (screen == 1) {
            changeCursor(screen, x, y + SCREEN1_START_POS);
        } else {
            changeCursor(screen, x, y + SCREEN2_START_POS);
        }
    }
}
