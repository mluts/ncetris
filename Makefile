FLAGS = -Wall -pedantic -std=gnu11 -DNDEBUG -g -ggdb
INC = -Isrc
CFLAGS = ${FLAGS} -c ${INC}
LFLAGS = ${FLAGS} -lcurses -lm
DIR_GUARD = mkdir -p ${@D}
CC = gcc
OBJECTS = obj/ts_board.o obj/ts_game.o obj/ts_loop.o obj/ts_piece.o obj/util.o

bin/ncetris: ${OBJECTS} obj/ncurses/ui.o obj/ncurses/main.o
	${DIR_GUARD}
	${CC} ${LFLAGS} $^ -o $@

test/test: ${OBJECTS} test/test.c
	${CC} ${INC} ${LFLAGS} -UNDEBUG $^ -o $@

obj/ncurses/%.o: src/ncurses/%.c src/ncurses/%.c
	${DIR_GUARD}
	${CC} ${CFLAGS} $< -o $@
obj/%.o: src/%.c src/%.h
	${DIR_GUARD}
	${CC} ${CFLAGS} $< -o $@
clean:
	rm -rf obj bin test/test

.PHONY: clean
