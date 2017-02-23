CC=gcc
EXE=nqueens
LINKER=-lncurses
CFLAGS=-Wall -Werror -g

default: all
all: nqueens
nqueens: main.c
	@${CC} ${CFLAGS} main.c ${LINKER} -o $@

clean:
	-@rm nqueens
