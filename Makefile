GCC = gcc -Wall -g -lcurses -lm

tetris: tetris.c
	${GCC} -o $@ $^
.PHONY: clean
