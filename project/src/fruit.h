#pragma once

#include "snake.h"


typedef struct {

	int x;				// x position
	int y;				// y position
	int active;			// ative
	
} Fruit;

Fruit* newFruit(double ix, double iy);
void eatFruit(Fruit * fruit, Snake * snake);

