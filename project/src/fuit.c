#include "fruit.h"

Fruit* initFruit()
{
	srand(time(NULL));
	int x= rand()%25; 
	int y= rand()%25;
	Fruit* fruit = malloc(sizeof(Fruit));
	fruit->fruitPosition = getPoint(x, y);
	fruit->fruitCoords = (Point*)pointToCoord(fruit->fruitPosition);
	return fruit; 
}

void eatFruit(Fruit* fruit)
{  
	srand(time(NULL));
	int x= rand()%25; 
	int y= rand()%25;
	fruit->fruitPosition = getPoint(x, y);
	fruit->fruitCoords = (Point*)pointToCoord(fruit->fruitPosition);
    return;	
} 

