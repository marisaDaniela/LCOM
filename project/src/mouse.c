#include "mouse.h"
// subscribe mouse
int g_hook3 =2;

int mouse_subscribe_int() {
	int bitmask = BIT(g_hook3);

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &g_hook3) != 0) {
		printf("System call sys_irqsetpolicy() failed! \n");
		return -1;
	}

	if (sys_irqenable(&g_hook3) != 0) {
		printf("System call sys_irqenable() failed! \n");
		return -1;
	}
	return bitmask;

}

// unsubscribe mouse
int mouse_unsubscribe_int() {
	if (sys_irqdisable(&g_hook3) != 0) {
		return -1;
	}
	if (sys_irqrmpolicy(&g_hook3) != 0) {
		return -1;
	}
	return 0;
}
