#pragma once

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "utils.h"
#include "i8042.h"


int mouse_subscribe_int() ;
int mouse_unsubscribe_int();

