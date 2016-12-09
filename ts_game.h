#ifndef _TS_GAME_H
#define _TS_GAME_H

#include <stdbool.h>
#include <stdint.h>
#include "ts_coord.h"
#include "ts_piece.h"

#define MAX_PIECES 64

typedef struct ts_Game {
  bool finished;
  uint8_t width, height;
  ts_Piece *piece;
  ts_Piece **frozenPieces;
  uint8_t frozenPiecesCount;
} ts_Game;

typedef void (*ts_Game_drawfn)(uint8_t y, uint8_t x);

ts_Game *ts_Game_new(uint8_t width, uint8_t height);
void ts_Game_destroy(ts_Game *);
void ts_Game_move(ts_Game *);
void ts_Game_draw(ts_Game *, ts_Game_drawfn);
void ts_Game_getBottomBorderCoords(ts_Game *, ts_Coord *, uint8_t length);
void ts_Game_getTopBorderCoords(ts_Game *, ts_Coord *, uint8_t length);
bool ts_Game_pieceDownCollision(ts_Game *game);
bool ts_Game_pieceUpCollision(ts_Game *game);
bool ts_Game_pieceLeftCollision(ts_Game *game);

#endif
