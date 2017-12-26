#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

#include "timer.h"
#include "kbd.h"
#include "mouse.h"

#include "utils.h"
#include "i8042.h"
#include "bitmap.h"

#define mode 0x117

int game();

