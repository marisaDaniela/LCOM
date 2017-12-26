#include "mouse.h"
#include "i8042.h"
// subscribe mouse

int g_hook3 = 2;

#define INPUT_bU BIT(1)

/**
 * @brief reads mouse packets from the controller
 * @param inf char pointer to save data
 * @return returns 0 in case of success
 */

int mouse_read(unsigned char *inf) {
	unsigned long inf_temp;
	unsigned long condition = 0;

	if(sys_inb(STAT_REG, &condition) != OK) {
		return -1;
	}
	if (condition & (OUT_BUF_FULL)) {
		if (sys_inb(OUT_BUF, &inf_temp) != OK) {
			return -1;
		}
	}

	*inf = (unsigned char) inf_temp;

	return 0;

}

/**
 * @brief writes mouse command to the keyboard controller
 * @param cmd to be sent
 * @return returns controller response in case of success, 1 otherwise
 */
int mouse_write(unsigned char cmd)
{
	unsigned char respond = 0;
	unsigned long respond_temp;
	sys_inb(STAT_REG, &respond_temp);

	if ((respond_temp & IN_BUF_FULL) == 0) {
		if (sys_outb(CMD_REG, WRITE_TO_MOUSE) != 0) {
			return 1;
		}

		if (sys_outb(IN_BUF_FULL, cmd) != 0) {
			return 1;
		}

		tickdelay(micros_to_ticks(DELAY));
		respond = (unsigned char) respond_temp;
		mouse_read(&respond);

		return respond;
	}
}

int mouse_subscribe_int() {
	int bitmask = BIT(g_hook3);

	mouse_write(STREAM_MODE_DISABLE);

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &g_hook3) != 0) {
		printf("System call sys_irqsetpolicy() failed! \n");
		return -1;
	}

	if (sys_irqenable(&g_hook3) != 0) {
		printf("System call sys_irqenable() failed! \n");
		return -1;
	}

	mouse_write(SET_STREAM_MODE);
	mouse_write(STREAM_ON);

	unsigned long in = 0;
	sys_inb(OUT_BUF, &in);

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

	mouse_write(STREAM_MODE_DISABLE);
	return 0;
}
