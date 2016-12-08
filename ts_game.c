#include "ts_game.h"
#include <stdlib.h>

ts_Game *ts_Game_new(uint8_t w, uint8_t h)
{
  ts_Game *game = calloc(1, sizeof(ts_Game));
  if(game != NULL) {
    game->width = w;
    game->height = h;
  }
  return game;
}

void ts_Game_destroy(ts_Game *game)
{ free(game); }
