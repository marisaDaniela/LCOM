#include "game.h"

int game()
{
	printf("IN GAME\n");

	// Init Timer
	int irq_timer = timer_subscribe_int();

	// Init Keyboard
	int irq_kbd = kbd_subscribe_int();

	// Init Mouse
	//int irq_mouse = mouse_subscribe_int();

	printf("TIMER: %d AND KBD: %d \n", irq_timer, irq_kbd);

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
	//sleep(3);

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
					printf("Subscribe timer\n");
				}

				if (msg.NOTIFY_ARG & irq_kbd)
				{
					printf("Subscribe keyboard\n");
					RUNNING = 0;
					
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
			printf("adeus \n");
		}
		printf("adeus2 \n");
	}


	if(timer_unsubscribe_int()!= 0){
		printf("Fail\n");
		return -1;
	}
	else
	{
		printf("Success\n");
	}
	int var;

	//printf("KBD_UNSUBSCRIBE %d\n", var);
	if((var = kbd_unsubscribe_int()) != 0){
		printf("KBD_UNS: %d\n", var);
		printf("NO no no!!");
		return -1;
	}
	else {
		printf("YAY!\n");
	}
	/*
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

	//vg_exit();
}
