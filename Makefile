FLAGS = -Wall -pedantic -std=gnu11 -DNDEBUG
INC = -Isrc
CFLAGS = ${FLAGS} -c -g ${INC}
LFLAGS = ${FLAGS} -lcurses -lm
DIR_GUARD = mkdir -p ${@D}
CC = gcc

bin/ncetris: src/ts_board.o src/ts_game.o src/ts_loop.o src/ts_piece.o src/util.o \
 	src/ncurses/ui.o src/ncurses/main.o
	${DIR_GUARD}
	${CC} ${LFLAGS} $^ -o $@

obj/%.o: src/%.c src/%.h
	${DIR_GUARD}
	${CC} ${CFLAGS} $< -o $@
clean:
	rm -rf obj bin
.PHONY: clean
