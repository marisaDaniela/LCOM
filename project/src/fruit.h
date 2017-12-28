#pragma once

#include "snake.h"
#include <minix/syslib.h>

typedef struct
{
	Point* fruitCoords;		
	Point* fruitPosition;	
	
} Fruit;

Fruit* initFruit();
void eatFruit();


