CC = gcc
CFLAGS = -g -Wall -std=c99 -D_GNU_SOURCE
LDLIBS = -lm

all: cross connect

cross: cross.o

cross.o: cross.c

connect: connect.o board.o

connect.o: connect.c board.h

board.o: board.c board.h

clean:
	rm -f cross cross.o
	rm -f connect connect.o board.o