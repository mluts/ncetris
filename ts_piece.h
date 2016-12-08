#ifndef _TS_PIECE_H
#define _TS_PIECE_H

#include "ts_coord.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
  J, L, S, Z, LINE, CUBE
} ts_PieceShape;

typedef struct {
  ts_Coord position;
  ts_PieceShape shape;
  uint8_t rotation;
} ts_Piece;

ts_Piece *ts_Piece_new();
void ts_Piece_destroy(ts_Piece *);
void ts_Piece_setshape(ts_Piece *, ts_PieceShape);
void ts_Piece_setposition(ts_Piece *, ts_Coord);
void ts_Piece_getcoords(ts_Piece *, ts_Coord*, uint8_t length);

#endif
