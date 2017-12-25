#include "fruit.h"

Fruit* newFruit(double ix, double iy)
{
	Fruit* fruit= (Fruit*) malloc(sizeof(Fruit)); 
	
	fruit->x = ix;
    fruit->y = iy;
    fruit->active = 1;
	
	return fruit; 
}

void eatFruit(Fruit * fruit, Snake * snake)
{ 

 
    return;	
} 
