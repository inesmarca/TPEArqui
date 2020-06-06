#include <keyboard.h>
#include <stdint.h>

static void int_21();

void irqDispatcher(uint64_t irq, uint64_t * stackFrame) {
	switch (irq) {
		case 1:
			int_21(stackFrame);
			break;
	}
	return;
}

void int_21(uint64_t * stackFrame) {
	keyboard_handler(stackFrame);
}
