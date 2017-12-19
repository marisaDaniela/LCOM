#include <minix/drivers.h>
#include "snake.h"

#include "graphics.h"
#include "kbd.h"

const int FPS = 25; //frames per second

Snake* initSnake(){
	Snake* snake = (Snake *) malloc(sizeof(Snake));

	snake->IRQ_SET_KBD = kbd_subscribe_int();

	snake->done = 0, snake->draw = 1;
	snake->scancode = 0;
	
	snake->lenght=1;
	snake->score=0;
	
	/*a ver
	snake->x_head=;
	snake->y_head=;
	snake->direction_head=;
	*/

	return snake;
}

