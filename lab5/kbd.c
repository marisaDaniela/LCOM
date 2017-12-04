#include "kbd.h"


// subscribe interruption


int g_hook=2;
int g_counter=0;
int kbd_subscribe_int() {
	int bitmask = BIT(g_hook);

	if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &g_hook) != 0) {
		printf("System call sys_irqsetpolicy() failed! \n");
		return -1;
	}

	if (sys_irqenable(&g_hook) != 0) {
		printf("System call sys_irqenable() failed! \n");
		return -1;
	}

	return bitmask;

}

// unsubscribe interruption

int kbd_unsubscribe_int() {
	if (sys_irqrmpolicy(&g_hook) != 0) {
		return -1;
	}
	if (sys_irqdisable(&g_hook) != 0) {
		return -1;
	}

	return 0;

}


// Function to read a key from the keyboard to be used by the function
// kbc_handler that prints makecode and breakcode

int kbc_read_key(unsigned char *key) {

	unsigned long key_tmp;
	unsigned long condition = 0;

	while(1) {
		sys_inb(STAT_REG, &condition);

		if ((condition & OUT_BUF_FULL) != 0) {
			if (sys_inb(OUT_BUF, &key_tmp) != OK) {
				return -1;
			}
			break;
		}
		tickdelay(micros_to_ticks(DELAY));
	}

	*key = (unsigned char) key_tmp;

	return 0;
}

// function to prints makecode and breakcode
// checks if the scancode is breakcode or makecode

int kbd_handler_c() {
	unsigned char key;
	unsigned short scancode;

	if(kbc_read_key(&key) != OK) {
		return -1;
	}

	if(key == 0xe0) {				// The codes e0 and e1 introduce scancode sequences.
		scancode = key << 8; 		// Apart from the Pause/Break key, that has an escaped sequence starting with e1, the escape used is e0. Often, // the codes are chosen in such a way that something meaningful happens when the receiver just discards the e0.

		if (kbc_read_key(&key) != OK) {
			return -1;
		}
		scancode |= key;
	}
	else
		scancode = key;

}

