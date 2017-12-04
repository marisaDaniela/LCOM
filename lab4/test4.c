#include "i8042.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "timer.c"


// subscribe teclado

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

// unsubscribe teclado

int kbd_unsubscribe_int() {
	if (sys_irqrmpolicy(&g_hook) != 0) {
		return -1;
	}
	if (sys_irqdisable(&g_hook) != 0) {
		return -1;
	}

	return 0;

}
// subscribe mouse
int mouse_subscribe_int() {
	printf("subscribe\n");
	int bitmask = BIT(g_hook);

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &g_hook) != 0) {
		printf("System call sys_irqsetpolicy() failed! \n");
		return -1;
	}

	if (sys_irqenable(&g_hook) != 0) {
		printf("System call sys_irqenable() failed! \n");
		return -1;
	}
	return bitmask;

}

// unsubscribe mouse
int mouse_unsubscribe_int() {
	printf("unsubscribe\n");
	if (sys_irqdisable(&g_hook) != 0) {
		return -1;
	}
	if (sys_irqrmpolicy(&g_hook) != 0) {
		return -1;
	}
	return 0;
}

// Functin to read data from mouse to be used by the function mouse_handler
// that will print the packages of mouse (TODO: see this, not sure yet)


int send_cmd_to_kbc(unsigned long port, unsigned long cmd) {
	unsigned long status;
	int ret;

	if ((ret = sys_inb(STAT_REG, &status)) != 0)
		return ret;

	if ((status & IN_BUF_FULL) == 0) {

		if((ret = sys_outb(port, cmd))!=0)
			return ret;
		else
			return 0;
	}
}

int mouse_write(unsigned long cmd) {
	int ret, respond = FALSE;
	unsigned long cmdToSend;

	while (!respond) {

		if((ret = send_cmd_to_kbc(STAT_REG, WRITE_TO_MOUSE)) != 0)
			return ret;
		else
			printf("send_cmd_to_kbc ok!\n");
		if((ret = send_cmd_to_kbc(OUT_BUF, cmd)) != 0 )
			return ret;
		else
			printf("send_cmd_to_kbc out_buf ok!\n");

		if((ret = sys_inb(OUT_BUF, &cmdToSend))!= 0)
			return ret;
		else
			printf("send_cmd_to_kbc cmdToSend ok!\n");

		if (cmdToSend == ACK){
			respond = TRUE;
			printf("cmdToSend: %x", cmdToSend);
			return 0;
		}
		else if (cmdToSend == ERROR) {
			printf("Send command failed!\n");
			return -1;
		}
	}
}

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

int send_packets() {
	int ret;

	if(sys_outb(STAT_REG, MOUSE_ENABLE)!=OK)
		return -1;

	ret = mouse_write(STREAM_MODE_DISABLE);
	printf("%d", ret);

	if (ret != 0)
		return ret;

	ret = mouse_write(STREAM_MODE_ENABLE);

	if (ret != 0)
		return ret;

	return mouse_write(SET_STREAM_MODE);
}

// Imprimir pacotes

void print_packet(unsigned char packet[3]) {

	char LB, MB, RB, XOVF, YOVF, xSign, ySign;
	int X, Y;

	LB = (packet[0] & BIT(0));
	RB = (packet[0] & BIT(1));
	MB = (packet[0] & BIT(2));
	XOVF = (packet[0] & BIT(6));
	YOVF = (packet[0] & BIT(7));
	xSign = (packet[0] & BIT(4));
	ySign = (packet[0] & BIT(5));

	X = packet[1];

	if (xSign)
	{
		X |= (-1 << 8);
	}

	Y = packet[2];
	if (ySign)
	{
		Y |= (-1 << 8);
	}

	printf("B1=0x%x  B2=0x%x  B3=0x%x  LB=%d  MB=%d  RB=%d  XOV=%d  YOV=%d  X=%d  Y=%d\n", packet[0], packet[1], packet[2],LB, MB, RB, XOVF,YOVF, X, Y);

}

// This function displays the packets received from the mouse
// Exits after receiving the number of packets specified in argument

int mouse_test_packet(unsigned short cnt) {
	unsigned char packet[3]; // array for a 3 byte packet
	int ipc_status;
	message msg;
	int ret, counter = 0;

	int irq_set = mouse_subscribe_int();
	ret = send_packets();

	if (irq_set == -1) {
		printf("test_packet()::error subscribing mouse interrupts..\n");
		return -1;
	}

	while (counter < (cnt*3) ) {  // counter_of_packets < cnt
		if (driver_receive(ANY, &msg, &ipc_status) != OK) {
			printf("test_packet()::driver_receive failed\n");
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set) {

					ret = mouse_read((&packet[counter % 3]));
					if (ret == -1)
						continue;
					if (ret != 0) {
						return ret;
					}
					if ((counter % 3 == 0) && ((packet[counter % 3] & BIT(3)) == 0)) {
						continue;
					}
					if ((counter % 3) == 2) {
						print_packet(packet);
					}
					counter++;
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
	}
	mouse_write(STREAM_MODE_DISABLE);
	printf("chegueii aquii\n");
	if(mouse_unsubscribe_int() == 0)
		return 0;
	else
	{
		printf("xpto");
		return -1;
	}
	//return mouse_unsubscribe_int();

}

int mouse_test_remote(unsigned long period, unsigned short cnt){
	unsigned char packet[3]; // array for a 3 byte packet
	int ipc_status;
	message msg;
	int ret, counter = 0;

	int irq_set = mouse_subscribe_int();
	int irq_set_timer = timer_subscribe_int();
	ret = send_packets();

	if (irq_set == -1) {
		printf("test_packet()::error subscribing mouse interrupts..\n");
		return -1;
	}
	if(irq_set_timer == -1) {
		printf("error subscribing timer interrupts..\n");
		return -1;
	}

	while (counter < (cnt*3)) {  // counter_of_packets < cnt
		if (driver_receive(ANY, &msg, &ipc_status) != OK) {
			printf("test_packet()::driver_receive failed\n");
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					sleep(period/2);
					timer_int_handler();				// subscrever o timer
					ret = mouse_read((&packet[counter % 3]));
					if (ret == -1)
						continue;
					if (ret != 0) {
						return ret;
					}
					if ((counter % 3 == 0) && (packet[counter % 3] && BIT(3) == 0))
					{
						continue;
					}
					if ((counter % 3) == 2) {
						print_packet(packet);
					}
					counter++;
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
	}
	mouse_write(STREAM_MODE_DISABLE);
	timer_unsubscribe_int();
	return mouse_unsubscribe_int();
}


int mouse_test_async(unsigned short idle_time){
	/* To be completed ... */
	return 0;
}

// TODO:

int mouse_test_gesture(short length){
	unsigned char packet[3]; // array for a 3 byte packet
	int ipc_status;
	message msg;
	int ret, counter = 0;

	int irq_set = mouse_subscribe_int();
	ret = send_packets();

	if (irq_set == -1) {
		printf("test_packet()::error subscribing mouse interrupts..\n");
		return -1;
	}

	while (1) {  // counter_of_packets < cnt
		if (driver_receive(ANY, &msg, &ipc_status) != OK) {
			printf("test_packet()::driver_receive failed\n");
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set) {

					ret = mouse_read((&packet[counter % 3]));
					if (ret == -1)
						continue;
					if (ret != 0) {
						return ret;
					}
					if ((counter % 3 == 0) && (packet[counter % 3] && BIT(3) == 0)) {
						continue;
					}
					if ((counter % 3) == 2) {
						print_packet(packet);
					}
					counter++;
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
	}
	mouse_write(STREAM_MODE_DISABLE);
	printf("chegueii aquii\n");
	if(mouse_unsubscribe_int() == 0)
		return 0;
	else
	{
		return -1;
	}
	//return mouse_unsubscribe_int();
}
