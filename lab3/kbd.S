#include "i8042.h"

.global _kbd_handler_assembly

_kbd_handler_assembly:
		xor		%eax, %eax
		mov $DELAY, %ecx

ciclo: 	inb $OUT_BUF
		ret
