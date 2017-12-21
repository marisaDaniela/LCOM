#include "kbd.h"
#include "timer.h"
#include "mouse.h"
#include "i8042.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "utils.h"

#define mode 0x114

int game();
