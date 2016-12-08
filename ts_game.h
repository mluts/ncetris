#ifndef _TS_GAME_H
#define _TS_GAME_H

#include <stdbool.h>
#include <stdint.h>

typedef struct ts_Game {
  bool finished;
  uint8_t width, height;
} ts_Game;

ts_Game *ts_Game_new(uint8_t width, uint8_t height);
void ts_Game_destroy(ts_Game *);
void ts_Game_move(ts_Game *);

#endif
