#pragma once

#include "timer.h"

typedef struct{
	int IRQ_SET_TIMER;			// to timer interrupts

} SnakeINT;

typedef struct {
	int x;				// x position
	int y;				// y position
	int direction;		// direction
} Coordinate;


typedef struct {
	unsigned int lenght; 	// snake's lenght
	Coordinate head;     	// snake's head

} Snake;

