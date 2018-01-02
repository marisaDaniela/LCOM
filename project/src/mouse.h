#pragma once
#include "utils.h"
#include "i8042.h"
#include "graphics.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

typedef struct {
	int x, y;
	int xSign, ySign;
	int xD, yD;
	double speed;

	int counter;
	unsigned long packet[3];

	int leftButtonDown;
	int rightButtonDown;

	int leftButtonReleased;
	int rightButtonReleased;

	int updated;
	int draw;
} Mouse;

int mouse_read(unsigned long *inf);
int mouse_write(unsigned long inf);
int mouse_subscribe_int();
int mouse_unsubscribe_int();

int mouseInside(Mouse* mouse, int xi,int xf,int yi,int yf); 
Mouse* newMouse();
Mouse* getMouse();
void drawMouse();
void updateMouse();
void deleteMouse(); 
