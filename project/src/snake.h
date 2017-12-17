#pragma once

#include "timer.h"

typedef struct {
	int IRQ_SET_TIMER;			// to timer interrupts
	int IRQ_SET_KBD;
	int done, draw;
	unsigned long scancode;
} Snake;

typedef struct {
	int x;				// x position
	int y;				// y position
	int direction;		// direction
} Coordinate;

typedef struct {
	unsigned int lenght; 	// snake's lenght
	Coordinate head;     	// snake's head
} SnakeObject;

Snake* initSnake();

void updateSnake(Snake* snake);
void drawSnake(Snake* snake);
void stopSnake(Snake* snake);
