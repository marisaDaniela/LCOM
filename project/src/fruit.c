#include "fruit.h"

Fruit* newFruit(double ix, double iy)
{
	Fruit* fruit= (Fruit*) malloc(sizeof(Fruit)); 
	
	fruit->x = ix;
    fruit->y = iy;
    fruit->active = true;
	
	return fruit; 
}

void eatFruit(Fruit * fruit, Snake * snake)
{ 
    /* Horizontally */
    if(snake->x_head < fruit->x || snake->x_head > fruit->x )
        return;
        
	/* Vertically */
    if(snake->y_head < fruit->y || snake->y_head > fruit->y )
        return;
 
    /* Eats fruits and adds to score */
    fruit->active = false;
    snake->score++;
    snake->lenght++; 
 
    return;	

} 
