#pragma once


typedef struct {

	int x;				// x position
	int y;				// y position
	bool active			// ative 
	
} Fruit;

Fruit* newFruit(double ix, double iy);
void eatFruit(Fruit * fruit, Snake * snake);

