#include "vbe.h"
#include "video_gr.h"
#include <unistd.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "video_test.h"
//#include "kbd.h"

#define MODE_105 0x105 //1024x768

void *video_test_init(unsigned short mode, unsigned short delay) {

	vbe_mode_info_t info;
	vbe_get_mode_info( mode, &info);

	void * vgInit = vg_init(mode);

	if( vgInit == NULL )
	{
		vg_exit();
		printf("test_init::failed vg_init()\n");
		return -1;
	}
	sleep(delay);

	vg_exit();

	printf(" VRAM: 0x%x\n", info.PhysBasePtr);

}


int video_test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

	void * vgInit = vg_init(MODE_105);
	//unsigned char key;

	if( vgInit == NULL )
	{
		vg_exit();
		printf("test_square::failed vg_init()\n");
		return -1;
	}

	drawSquare(x,y,size,color);
	video_dump_fb();

	sleep(5);


	//TODO: KeyESC pressed to leave

	vg_exit();
	return 0;

}

int video_test_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color) {

	void * vgInit = vg_init(MODE_105);

	if( vgInit == NULL )
	{
		vg_exit();
		printf("test_square::failed vg_init()\n");
		return -1;
	}

	drawLine(xi,yi,xf, yf,color);
	video_dump_fb();
	sleep(5);

	//TODO: KeyESC pressed to leave

	vg_exit();
	return 0;

}


int video_test_xpm(char *xpm[], unsigned short xi, unsigned short yi) {

	return 0;

}

int video_test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short s, unsigned short f) {

	/* To be completed */
	return 0;

}

int video_test_controller() {

	/* To be completed */
	return 0;
}
