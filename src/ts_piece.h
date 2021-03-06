#ifndef _TS_PIECE_H
#define _TS_PIECE_H

#include "ts_pos.h"
#include <stdint.h>

#define NUM_TETROMINOS 7
#define NUM_ORIENTATIONS 4
#define NUM_TETROMINO_SIZE 4

#define RANDOM_TETROMINO (rand()%NUM_TETROMINOS)

#define TETROMINO_J 0
#define TETROMINO_L 1
#define TETROMINO_3 2
#define TETROMINO_I 3
#define TETROMINO_Z 4
#define TETROMINO_S 5
#define TETROMINO_O 6

typedef struct {
  int8_t type, orientation;
  ts_Pos pos;
} ts_Piece;

extern const ts_Pos TETROMINOS[NUM_TETROMINOS][NUM_ORIENTATIONS][NUM_TETROMINO_SIZE];

ts_Piece *ts_Piece_new(int8_t type);
void ts_Piece_destroy(ts_Piece *);
void ts_Piece_rotate(ts_Piece *, int8_t direction);
void ts_Piece_move(ts_Piece *, int8_t dy, int8_t dx);
ts_Pos ts_Piece_pos(const ts_Piece *, int8_t n);
#endif
