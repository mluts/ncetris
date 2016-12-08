GCC = gcc -Wall -g -lcurses -lm

tetris: tetris.c
	${GCC} -o $@ $^
clean:
	rm -f tetris
.PHONY: clean
