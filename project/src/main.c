#include <stdio.h>
#include "vbe.h"
#include "graphics.h"
#include "snake.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	sef_startup();

	void * vgInit = vg_init(0x114);
	if( vgInit == NULL )
	{
		vg_exit();
		printf("test_square::failed vg_init()\n");
		return -1;
	}

	unsigned char key;

	Snake* snake = (Snake*)startSnake();

	/*while(!snake->done) {
		updateSnake(snake);

		if (!snake->done) {
			if (snake->draw)
				drawSnake(snake);
		}
	}*/
	drawSquare(20,20,500,1);


	stopSnake(snake);


	sleep(5);


	//TODO: KeyESC pressed to leave

	vg_exit();
	return 0;
}
