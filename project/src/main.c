#include <stdio.h>
#include "vbe.h"
#include "graphics.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	sef_startup();


	printf("Hello, world!\n");
	unsigned short color = 1;
	printf("NUM:%us", color);

	//void * vgInit = vg_init(0x114);
	//unsigned char key;

//	if( vgInit == NULL )
//	{
//		vg_exit();
//		printf("test_square::failed vg_init()\n");
//		return -1;
//	}


	drawSquare(20,20,500,color);

	sleep(5);


	//TODO: KeyESC pressed to leave

	//vg_exit();
	return 0;
}
