#include <stdio.h>
#include "vbe.h"
#include "graphics.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	sef_startup();


	printf("Hello, world!\n");

	void * vgInit = vg_init(0x114);
	//unsigned char key;

	if( vgInit == NULL )
	{
		vg_exit();
		printf("test_square::failed vg_init()\n");
		return -1;
	}

	drawSquare(20,20,500,600);

	sleep(5);


	//TODO: KeyESC pressed to leave

	vg_exit();
	return 0;
}
