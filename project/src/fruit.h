#pragma once

#include "snake.h"
#include <minix/syslib.h>

typedef struct
{
	Point* fruitCoords;		
	Point* fruitPosition;	
	int value; 
	int special; 
	unsigned int timer;
	unsigned int duration;  
	
} Fruit;

Fruit* initFruit();
int eatFruit();
void updatepositionF(Fruit* fruit);
Fruit* specialFruit(); 

