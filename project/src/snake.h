#pragma once
#include "point.h"
#include "utils.h"
#include "fruit.h"
#include "i8042.h"

#define INIT_SIZE 3

typedef enum
{
	LEFT, RIGHT, UP, DOWN
} Direction;

typedef struct
{
	int score; 
	Direction direction;	// snake's direction
	unsigned int size; 		// snake's size
	Point** snakePosition;	// snake[0] is the tail snake[size - 1] is the head
} Snake;

Snake* initSnake();
void updateSnake(Snake* snake);
void drawSnake(Snake* snake);
void stopSnake(Snake* snake);

