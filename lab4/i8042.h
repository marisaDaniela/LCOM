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

// MOUSE

/**
Stream Mode The mouse sends the data packet at a (programmable)
maximum fixed rate to the KBC, as determined by “mouse events”,
i.e. mouse movements and changes in buttons state

Remote Mode The mouse sends data packets only upon request of
the KBC*/

#define MOUSE_IRQ 				12

#define ACK						0xFA 		// if everything OK
#define NACK 					0xFE 		// if invalid
#define ERROR 					0xFC 		// second consecutive invalid byte

// PS/2 Mouse Commands

#define STREAM_MODE_DISABLE		0xF5
#define STREAM_MODE_ENABLE		0xF4
#define SET_STREAM_MODE			0xEA
#define STATUS_REQUEST 			0xE9

#define WRITE_TO_MOUSE 			0xD4
#define MOUSE_ENABLE			0xA8
#define MOUSE_DISABLE 			0xA7

// Computer Labs: The PS/2 Mouse (slide 4)

#define MOUSE_LB 				BIT(0)
#define MOUSE_RB 				BIT(1)
#define MOUSE_MB 				BIT(2)
#define MOUSE_UNUSED 			BIT(3)
#define MOUSE_X_SIGN 			BIT(4)
#define MOUSE_Y_SIGN 			BIT(5)
#define MOUSE_X_OVF 			BIT(6)
#define MOUSE_Y_OVF 			BIT(7)

#endif /* _I8042_H_ */
