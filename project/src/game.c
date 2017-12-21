#include "game.h"
#include "bitmap.h"

int game()
{
	int ipc_status, r;
	message msg;
	int RUNNING = 1;

	if(lm_init()==NULL){
		return;
	}

	char *video_mem;
	video_mem = vg_init(mode);

	if(video_mem == NULL){
		return;
	}

	initDoubleBuffer();

	//subscrever as interrupcoes do timer
	int irq_timer = timer_subscribe_int();

	//subscrever as interrupcoes do teclado
	int irq_kbd = kbd_subscribe_int();


	//subscrever as interrupcoes do rato
	int irq_mouse = mouse_subscribe_int( );


	Bitmap* lcom = loadBitmap(path('lcom'));
	clearBuffer();
	drawBitmap('lcom', 261, 133, ALIGN_LEFT);

	bufferToVideoMem();

	while(RUNNING) {
		if (driver_receive(ANY, &msg, &ipc_status) != OK) {
			printf("driver_receive failed with: %d\n",r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {

			//received notification
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_timer) {
					printf("interrupt timer\n");

				}

				if (msg.NOTIFY_ARG & irq_kbd) {
					printf("interrupt keyboard\n");

				}

				/*if (msg.NOTIFY_ARG & irq_mouse) {
					printf("interrupt mouse\n");

				}*/

				break;
			}
		}

		mouse_unsubscribe_int();
		kbd_unsubscribe_int();
		timer_unsubscribe_int();
		RUNNING = 0;
	}


}
