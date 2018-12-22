CC=gcc
EXE=nqueens
LINKER=-lncurses
CFLAGS=-Wall -Werror -g

default: all
all: nqueens
nqueens: main.c grid.c
	@${CC} ${CFLAGS} main.c grid.c ${LINKER} -o $@

clean:
	-@rm nqueens
