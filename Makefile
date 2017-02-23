CC=gcc
EXE=nqueens
LINKER=-lncurses

default: all
all: nqueens
nqueens: main.c
	${CC} main.c ${LINKER} -o $@

