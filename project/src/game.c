#include "game.h"

int game()
{
	srand(time(NULL));
	// Init Timer
	int irq_timer = timer_subscribe_int();

	// Init Keyboard
	int irq_kbd = kbd_subscribe_int();

	// Init Mouse
	int irq_mouse = mouse_subscribe_int();	

	// Init Graphics
	lm_init();
	char *video_mem = (char*) vg_init(mode);

	if(video_mem == NULL)
	{
		return;
	}

	initDoubleBuffer();

	// Load Bitmaps
	Bitmap* menu = loadBitmap(path("blueSquare"));
	Bitmap* board = loadBitmap(path("board"));
	Bitmap* snakeHead = loadBitmap(path("snakeBody"));
	Bitmap* snakeBody = loadBitmap(path("snakeBody"));
	Bitmap* food = loadBitmap(path("food"));
	Bitmap* special = loadBitmap(path("blueSquareBackup")); 
	Bitmap* cursor = loadBitmap(path("blueSquareBackup"));

	// Load Entities
	Snake* snake = initSnake();
	Fruit* fruit = initFruit();
	Fruit* specialF = specialFruit(); 

	// Game Loop
	int finalscore=0; 
	int ipc_status, r;
	message msg;
	int difficulty = 9;
	int timer = 0;
	int time_bound = 60 / difficulty;
	int RUNNING = 1;
	char gamest= 'M';


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
					switch (gamest)
					{
					case 'M': 
						// Clear the buffer
						clearBuffer();

						// Draw board
						drawBitmap(menu, BOARD_X, BOARD_Y, ALIGN_LEFT);
						
						// Draw mouse
						drawBitmap(cursor, getMouse()->x, getMouse()->y, ALIGN_LEFT);
					
							
						if(mouseInside(getMouse(), 5 , 20, 15, 20) && getMouse()->leftButtonDown)						
						{
							gamest='G'; 
						}
						/*if(mouseInside(getMouse(), 5, 20, 5, 10) && getMouse()->leftButtonDown)
						{
							RUNNING = 0;
						}	*/
						// Buffer to Video Memory
						bufferToVideoMem();				
					break; 
					case 'G': 
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

						drawBitmap(food, fruit->fruitCoords->x, fruit->fruitCoords->y, ALIGN_LEFT);
						
						// Move Snake
						if(timer >= time_bound)
						{
							timer -= time_bound;
							finalscore = moveSnake(snake, fruit, specialF);
						}

						//Draw special Food
						if(specialF->timer != 0)
						{
							specialF->timer--;
						}
						else
						{
							if(specialF->duration == 0)
							{
								deleteBitmap(special);
							}
							else
							{
								drawBitmap(special, specialF->fruitCoords->x, specialF->fruitCoords->y, ALIGN_LEFT); 
								specialF->duration--; 
							}
						}
							
						// Buffer to Video Memory
						bufferToVideoMem();
						break;
					}
				}

				if (msg.NOTIFY_ARG & irq_kbd)
				{				
					unsigned short key = kbd_handler_c();
					
					if (key == SPACE)
					{
						gamest= 'G'; 
					}
					
					if (key == SNAKE_W || key == SNAKE_S ||	key == SNAKE_D || key == SNAKE_A)	
					{
						updateDirection(snake, key);
					}
					
					if (key == ESC)
					{
						RUNNING = 0;
					}
					continue;
				}

				if (msg.NOTIFY_ARG & irq_mouse)
				{
					updateMouse();
				}

				break;
			}
		}
	}

	timer_unsubscribe_int();
	kbd_unsubscribe_int();
	mouse_unsubscribe_int();

	vg_exit();
}
