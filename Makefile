GCC = gcc -Wall -g -lcurses -lm -std=c11 -DNDEBUG

test: test.c ts_piece.h ts_piece.o ts_game.h ts_game.o ts_coord.h ts_coord.o \
	util.h
	${GCC} -UNDEBUG -o $@ ts_game.o ts_piece.o ts_coord.o test.c
ts_piece.o: ts_piece.c ts_piece.h
	${GCC} -c -o $@ ts_piece.c
ts_game.o: ts_game.c ts_game.h
	${GCC} -c -o $@ ts_game.c
ts_coord.o: ts_coord.c ts_coord.h
	${GCC} -c -o $@ ts_coord.c
ts_loop.o: ts_loop.c ts_loop.h
	${GCC} -c -o $@ ts_loop.c
clean:
	rm -f ts_piece.o ts_game.o ts_coord.o test
.PHONY: clean
