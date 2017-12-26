#include <stdio.h>
#include "game.h"
#include "snake.h"
#include "utils.h"

int main(int argc, char **argv)
{
	/*
	Snake* snake = initSnake();
	Point* foodPosition = getPoint(0,0);
	printf("BEFORE MOVING X: %d AND Y: %d", snake->snakePosition[2]->x, snake->snakePosition[2]->y);
	NEWLINE;

	moveSnake(snake, foodPosition);

	printf("AFTER MOVING X: %d AND Y: %d", snake->snakePosition[2]->x, snake->snakePosition[2]->y);
	NEWLINE;
	*/

	printf("Entering Game\n");
	srand(time(NULL));
	game();

	// printf("\n\n\n");
	return;
}

