#include <minix/drivers.h>
#include "snake.h"

const int FPS = 25; //frames per second

Snake* initSnake()
{
	Snake* snake = (Snake *) malloc(sizeof(snake));

	snake->size = INIT_SIZE;
	
	snake->snakePosition = malloc(INIT_SIZE * sizeof(Point));
	snake->snakePosition[0] = getPoint(0,0);
	snake->snakePosition[1] = getPoint(1,0);
	snake->snakePosition[2] = getPoint(2,0);

	snake->direction = RIGHT;

	return snake;
}

void moveSnake(Snake* snake, Point* foodPosition)
{
	// Calculate new head position
	Point* headPosition = snake->snakePosition[snake->size - 1];

	switch(snake->direction)
	{
	case LEFT:
		headPosition->x -= 1;
		break;

	case RIGHT:
		headPosition->x += 1;
		break;

	case UP:
		headPosition->y -= 1;
		break;

	case DOWN:
		headPosition->y += 1;
		break;

	default:
		printf("Error\n");
		break;
	}

	// Save old body
	Point** oldBody = snake->snakePosition;

	// Check if food eaten
	if(comparePoints(headPosition, foodPosition))
	{
		// Food eaten

		// Size increases
		snake->size += 1;
		snake->snakePosition = malloc(snake->size * sizeof(Point));

		// Regenerate body
		unsigned int i;
		for(i = 0; i < (snake->size - 1); i++)
		{
			snake->snakePosition[i] = oldBody[i];
		}
	}
	else
	{
		// Food not eaten

		// Regenerate body
		unsigned int i;
		for(i = 1; i < (snake->size - 1); i++)
		{
			snake->snakePosition[i - 1] = oldBody[i];
		}
	}

	// Place head
	snake->snakePosition[snake->size - 1] = headPosition;
}
