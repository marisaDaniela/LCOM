#include "game.h"

int game()
{
	printf("IN GAME\n");

	// Init Timer
	int irq_timer = timer_subscribe_int();

	// Init Keyboard
	int irq_kbd = kbd_subscribe_int();

	// Init Mouse
	int irq_mouse = mouse_subscribe_int();

	printf("TIMER: %d AND KEYBOARD: %d\n", irq_timer, irq_kbd);

	// Init Graphics

	/*
	if(lm_init()==NULL)
	{
		return;
	}

	char *video_mem = vg_init(mode);

	if(video_mem == NULL)
	{
		return;
	}

	initDoubleBuffer();
	clearBuffer();
	
	// Load bitmaps

	Bitmap* blueSquare = loadBitmap(path("blueSquare"));
	Bitmap* board = loadBitmap(path("board"));
	Bitmap* snakeBody = loadBitmap(path("snakeBody"));

	drawBitmap(blueSquare, 0, 0, ALIGN_LEFT);
	drawBitmap(board, 242, 114, ALIGN_LEFT);
	bufferToVideoMem();

	sleep(10);
	*/

	// game loop
	int ipc_status, r;
	message msg;
	int RUNNING = 1;
	printf("entering game loop");
	NEWLINE;

	sleep(5);

	while(RUNNING)
	{
		if (driver_receive(ANY, &msg, &ipc_status) != OK)
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
					printf("interrupt timer\n");
				}

				if (msg.NOTIFY_ARG & irq_kbd)
				{
					RUNNING = 0;
					printf("interrupt keyboard\n");
				}

				/*
				if (msg.NOTIFY_ARG & irq_mouse)
				{
					printf("interrupt mouse\n");
				}
				*/

				break;
			}
		}
	}

	mouse_unsubscribe_int();
	kbd_unsubscribe_int();
	timer_unsubscribe_int();
	//vg_exit();
}
