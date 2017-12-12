#include <minix/drivers.h>
#include "snake.h"

#include "graphics.h"
#include "kbd.h"
#include "i8042.h"

const int FPS = 25; //frames per second

Snake* startSnake() {
	Snake* snake = (Snake *) malloc(sizeof(Snake));

	snake->IRQ_SET_KBD = kbd_subscribe_int();
	snake->IRQ_SET_TIMER = timer_subscribe_int();

	snake->done = 0, snake->draw = 1;
	snake->scancode = 0;

	return snake;
}

void updateSnake(Snake* snake) {
	int ipc_status, r = 0;
	message msg;

	if(driver_receive(ANY, &msg, &ipc_status) != 0)
		return;
	if(is_ipc_notify(ipc_status)) {
		switch(_ENDPOINT_P(msg.m_source)){
		case HARDWARE:
			if(msg.NOTIFY_ARG & snake->IRQ_SET_KBD)
				snake->scancode = kbd_handler_c();
			break;
		default:
			break;
		}
	}
	if(snake->scancode != 0) {
		if(snake->scancode == ESC)
		{
			snake->done = 1;
		}
	}
}

void drawSnake(Snake* snake) {
	fillDisplay(1);
}

void stopSnake(Snake* snake) {
	kbd_unsubscribe_int();
	timer_unsubscribe_int();

	free(snake);

}

