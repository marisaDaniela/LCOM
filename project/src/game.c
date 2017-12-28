#include "game.h"

int game()
{
	srand(time(NULL));
	
	// Init Timer
	int irq_timer = timer_subscribe_int();

	// Init Keyboard
	int irq_kbd = kbd_subscribe_int();

	// Init Mouse
	//int irq_mouse = mouse_subscribe_int();

	// Init Graphics
	lm_init();
	char *video_mem = (char*) vg_init(mode);

	if(video_mem == NULL)
	{
		return;
	}

	initDoubleBuffer();

	// Load Bitmaps
	Bitmap* blueSquare = loadBitmap(path("blueSquare"));
	Bitmap* board = loadBitmap(path("board"));
	Bitmap* snakeHead = loadBitmap(path("snakeBody"));
	Bitmap* snakeBody = loadBitmap(path("snakeBody"));
	Bitmap* food = loadBitmap(path("food"));

	// Load Entities
	Snake* snake = initSnake();
	Fruit* fruit = initFruit();

	// Game Loop
	int ipc_status, r;
	message msg;
	int difficulty = 6;
	int timer = 0;
	int time_bound = 60 / difficulty;
	int RUNNING = 1;


	while(RUNNING)
	{
		if (r = driver_receive(ANY, &msg, &ipc_status) != 0)
		{
			printf("driver_receive failed with: %d\n",r);
			continue;
		}
		if (is_ipc_notify(ipc_status))
		{
			switch (_ENDPOINT_P(msg.m_source))
			{
			//received notification
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_timer)
				{
					// Update timer
					timer++;

					// Clear the buffer
					clearBuffer();

					// Draw board
					drawBitmap(board, BOARD_X, BOARD_Y, ALIGN_LEFT);

					// Draw snake
					Point** positions = snake->snakePosition;

					unsigned int i;
					for(i = 0; i < snake->size; i++)
					{
						Point* currPos = positions[i];
						Point* coords = (Point*)pointToCoord(currPos);

						if(i == (snake->size - 1))
						{
							// Head
							drawBitmap(snakeHead, coords->x, coords->y, ALIGN_LEFT);
						}
						else
						{
							// Body
							drawBitmap(snakeBody, coords->x, coords->y, ALIGN_LEFT);
						}
					}

					// Draw food
					//Point* foodCoords = (Point*)pointToCoord(food->foodPosition);

					drawBitmap(food, fruit->fruitCoords->x, fruit->fruitCoords->y, ALIGN_LEFT);

					// Move Snake
					if(timer >= time_bound)
					{
						timer -= time_bound;
						moveSnake(snake, fruit);
					}

					// Buffer to Video Memory
					bufferToVideoMem();
				}

				if (msg.NOTIFY_ARG & irq_kbd)
				{
					unsigned short key = kbd_handler_c();

					printf("%i", key);

					updateDirection(snake, key);

					if (key == ESC)
					{
						RUNNING = 0;
					}
				}

/*
				if (msg.NOTIFY_ARG & irq_mouse)
				{
					RUNNING = 0;
					printf("Subscribe mouse\n");
				}
*/
				break;
			}
		}
	}

	timer_unsubscribe_int();
	kbd_unsubscribe_int();

	/* UNSUBSCRIBE MOUSE
	int var2;
	if((var2 = mouse_unsubscribe_int()) != 0)
	{
		printf("MOUSE_UNS: %d\n", var2);
		printf("Oh no\n");
	}
	else
	{
		printf("YAYYY!\n");
		return 0;
	}*/

	vg_exit();
}

