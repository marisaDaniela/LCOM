#pragma once

#include "i8042.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

int mouse_subscribe_int() ;
int mouse_unsubscribe_int();
