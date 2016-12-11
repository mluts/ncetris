#ifndef _TS_GAME_H
#define _TS_GAME_H
#include <stdint.h>
#include <sys/time.h>
#include "ts_board.h"
#include "ts_piece.h"

typedef struct {
  bool finished;
  ts_Board *board;
  ts_Piece *failing;
} ts_Game;

typedef enum {
  TS_LEFT, TS_RIGHT, TS_ROTATE_CW, TS_ROTATE_CCW, TS_DOWN
} ts_Movement;

ts_Game *ts_Game_new(ts_BoardDimension width, ts_BoardDimension height);
void ts_Game_destroy(ts_Game *);
void ts_Game_fall(ts_Game *);
bool ts_Game_isfinished(ts_Game *);
void ts_Game_move(ts_Game *, ts_Movement);

#endif
