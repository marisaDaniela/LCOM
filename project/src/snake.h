#pragma once

#include "timer.h"

typedef struct {
	int IRQ_SET_TIMER;			// to timer interrupts
	int IRQ_SET_KBD;
	int done, draw;
	unsigned long scancode;
	
	/*
	int x;						// x position
	int y;						// y position
	*/
	
	unsigned int score; 
	unsigned int lenght; 		// snake's lenght
	
	// snake's head coord
	int x_head;     				
	int y_head; 	
	int direction_head;			// direction

} Snake;

Snake* initSnake();

void updateSnake(Snake* snake);
void drawSnake(Snake* snake);
void stopSnake(Snake* snake);

