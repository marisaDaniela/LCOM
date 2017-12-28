#include <minix/drivers.h>
#include "snake.h"

const int FPS = 25; //frames per second

Snake* initSnake()
{
	Snake* snake = malloc(sizeof(Snake));

	snake->size = INIT_SIZE;
	
	snake->snakePosition = malloc(INIT_SIZE * sizeof(snake->snakePosition));
	snake->snakePosition[0] = getPoint(0,0);
	snake->snakePosition[1] = getPoint(1,0);
	snake->snakePosition[2] = getPoint(2,0);

	snake->direction = RIGHT;

	return snake;
}

void die(Snake* snake)
{
	snake->size = INIT_SIZE;
	
	snake->snakePosition = malloc(INIT_SIZE * sizeof(snake->snakePosition));
	snake->snakePosition[0] = getPoint(0,0);
	snake->snakePosition[1] = getPoint(1,0);
	snake->snakePosition[2] = getPoint(2,0);

	snake->direction = RIGHT;
	return;
}

void moveSnake(Snake* snake, Fruit* fruit)
{
	// Calculate new head position
	Point* headPosition = snake->snakePosition[snake->size - 1];

	// Save old body
	Point** oldBody = malloc(sizeof(oldBody));

	unsigned int i = 0;
	for(i = 0; i < snake->size; i++)
	{
		oldBody[i] = getPoint(snake->snakePosition[i]->x, snake->snakePosition[i]->y);
	}

	// Move head
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

	// Check if goes against boarders
	if(headPosition->x < 0 || headPosition->x >= 25 || headPosition->y < 0 || headPosition->y >= 25)
	{
		// Dead
		die(snake);
		return;
	}
	// Check if goes against herself
	int b;
	Point* bodyPosition;
	for(b=0; b < snake->size - 1; b++)
	{
		bodyPosition = snake->snakePosition[b];
		
		if (comparePoints(headPosition, bodyPosition))
		{
			die(snake);	
			return; 		
		}
	}	

	// Check if food eaten
	if(comparePoints(headPosition, fruit->fruitPosition))
	{
		// Food eaten
		eatFruit(fruit);
		// Save head
		Point* head = getPoint(headPosition->x, headPosition->y);

		// Size increases
		snake->size += 1;
		snake->snakePosition = malloc(snake->size * sizeof(snake->snakePosition));

		// Regenerate body
		unsigned int i;
		for(i = 0; i < (snake->size - 1); i++)
		{
			snake->snakePosition[i] = oldBody[i];
		}
		snake->snakePosition[snake->size - 1] = head;
	}
	else
	{
		// Food not eaten

		printf("\nFood eaten\n");

		// Regenerate body
		unsigned int i;
		for(i = 1; i < snake->size; i++)
		{
			snake->snakePosition[i - 1] = oldBody[i];
		}
	}
}

void printSnakePosition(Snake* snake)
{
	printf("PRINTING YOUR SNAKE:\n");

	unsigned int i = 0;
	for(i = 0; i < snake->size; i++)
	{
		printf("X: %d AND Y: %d\n", snake->snakePosition[i]->x, snake->snakePosition[i]->y);
	}

	printf("FINISHED PRINTING YOUR SNAKE:\n");
}

void updateDirection(Snake* snake, unsigned short key)
{
	switch(key)
	{
	case SNAKE_A:

		snake->direction = LEFT;
		break;

	case SNAKE_D:

		snake->direction = RIGHT;
		break;

	case SNAKE_W:

		snake->direction = UP;
		break;

	case SNAKE_S:

		snake->direction = DOWN;
		break;

	default:
		// DO NOTHING
		break;
	}
}

