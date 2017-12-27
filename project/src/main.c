#include <stdio.h>
#include "game.h"
#include "snake.h"
#include "utils.h"

int main(int argc, char **argv)
{
	/*
	Snake* snake = initSnake();

	printSnakePosition(snake);

	Point* foodPosition = getPoint(10, 10);

	moveSnake(snake, foodPosition);

	NEWLINE;

	printSnakePosition(snake);

	return;
	*/

	printf("Entering Game\n");
	srand(time(NULL));
	game();

	return;
}
