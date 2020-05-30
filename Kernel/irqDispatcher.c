#include <keyboard.h>
#include <stdint.h>

static void int_21();

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 1:
			int_21();
			break;
	}
	return;
}

void int_21() {
	keyboard_handler();
}
