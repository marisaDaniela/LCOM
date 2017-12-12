COMPILER_TYPE = gnu

CC = gcc

PROG = project
SRCS = graphics.c kbd.c main.c snake.c timer.c utils.c vbe.c 

CCFLAGS= -Wall -O3

DPADD += ${LIBDRIVER} ${LIBSYS}
LDADD += -llm -ldriver -lsys

LDFLAGS += -L.

MAN=
BINDIR? = /usr/sbin

.include <bsd.prog.mk>
.include <bsd.gcc.mk>