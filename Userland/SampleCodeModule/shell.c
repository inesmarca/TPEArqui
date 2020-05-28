#include <libC.h>
#include <screenManager.h>


void shell() {
    while (!getExitFlag()) {
        drawBlock(pos1X, pos1Y);
        while (getScreen() == 1) {
            printKey(1);
        }
        blankBlock(pos1X, pos1Y);
        drawBlock(pos2X, pos2Y);
        while (getScreen() == 2) {
            printKey(2);
        }
        blankBlock(pos2X, pos2Y);
    }
}
