#ifndef _TS_BOARD_H
#define _TS_BOARD_H
#include <stdint.h>
#include <stdbool.h>
#include "ts_piece.h"
#include "ts_pos.h"

#define BOARD_EMPTY 0
#define BOARD_PIECE(piece) (BOARD_EMPTY+piece->type+1)
#define BOARD_PIECE_TYPE(ch) (ch-BOARD_EMPTY-1)

typedef int16_t ts_BoardDimension;
typedef uint8_t ts_BoardChar;

typedef struct {
  ts_BoardDimension width, height;
  ts_BoardChar *board;
} ts_Board;

ts_Board *ts_Board_new(ts_BoardDimension width, ts_BoardDimension height);
void ts_Board_destroy(ts_Board *);
void ts_Board_put_piece(ts_Board *, const ts_Piece *);
void ts_Board_remove_piece(ts_Board *, const ts_Piece *);
void ts_Board_set(ts_Board *, const ts_Pos *, ts_BoardChar value);
ts_BoardChar ts_Board_get(const ts_Board *, const ts_Pos *);
void ts_Board_unset(ts_Board *, const ts_Pos *);
bool ts_Board_piecefits(const ts_Board *, const ts_Piece *);
void ts_Board_copy(ts_Board *from, ts_Board *to);
bool ts_Board_changed(ts_Board *, ts_Board *);
#endif
