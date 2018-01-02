#include "fruit.h"

Fruit* initFruit()
{
	srand(time(NULL));
	int x= rand()%25; 
	int y= rand()%25;
	Fruit* fruit = malloc(sizeof(Fruit));
	fruit->fruitPosition = getPoint(x, y);
	fruit->fruitCoords = (Point*)pointToCoord(fruit->fruitPosition);
	fruit->timer = 0; 
	fruit->value = 5; 
	fruit->special=1; 
	return fruit; 
}

int eatFruit(Fruit* fruit)
{  if(fruit->special==0)
	{
		srand(time(NULL));
		fruit->timer=rand()%6; 
		fruit->duration=5; 
		updatepositionF(fruit); 
    	return fruit->value;
	}
	else
	{
		srand(time(NULL));
		updatepositionF(fruit); 
    	return fruit->value;	
    }
} 

void updatepositionF(Fruit* fruit)
{
	srand(time(NULL)); 
	int x= rand()%25; 
	int y= rand()%25;
	fruit->fruitPosition = getPoint(x, y);
	fruit->fruitCoords = (Point*)pointToCoord(fruit->fruitPosition);
	return; 

}

Fruit* specialFruit()
{
	srand(time(NULL));
	int x= rand()%25; 
	int y= rand()%25;
	Fruit* fruit = malloc(sizeof(Fruit));
	fruit->fruitPosition = getPoint(x, y);
	fruit->fruitCoords = (Point*)pointToCoord(fruit->fruitPosition);
	fruit->timer=rand()%5; 
	fruit->value = 15; 
	fruit->duration=5; 
	fruit->special=0; 
	
	return fruit; 
}
