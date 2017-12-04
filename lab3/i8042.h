#ifndef _I8042_H_
#define _I8042_H_

#define BIT(n) 				(0x01<<(n))
#define BREAK_CODE_BIT 		BIT(7)

#define ESC					0x81

// KBC REGISTERS

#define STAT_REG 			0x64
#define KBC_CMD_REG 		0x64
#define IN_BUF 				0x60
#define OUT_BUF		 		0x60

#define KBD_IRQ				0x01

#define OUT_BUF_FULL 		BIT(0)
#define IN_BUF_FULL 		BIT(1)

#define DELAY				20000


#endif /* _I8042_H_ */
