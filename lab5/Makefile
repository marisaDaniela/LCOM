# Makefile for lab5

COMPILER_TYPE= gnu

CC=gcc

PROG= lab5

SRCS= lab5.c vbe.c video_gr.c test5.c video_test.c kbd.c

CFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}

LDADD+= -llm -lsys -ldriver 
LDFLAGS+= -L .

MAN=

BINDIR?= /usr/sbin
.include <bsd.prog.mk>
.include <bsd.gcc.mk>