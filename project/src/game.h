#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

#include "timer.h"
#include "kbd.h"
#include "mouse.h"

#include "i8042.h"
#include "bitmap.h"

#include "utils.h"

#include "snake.h"

#define mode 0x117

int game();

void printSnakePosition(Snake* snake);
