#ifndef _NCURSES_UI_H
#define _NCURSES_UI_H
#include <ncurses.h>
#include "ts_game.h"

typedef struct {
  WINDOW *board;
  int16_t boardWidth, boardHeight;
} ts_ui;

ts_ui *ts_ui_new(int16_t boardWidth, int16_t boardHeight);
void ts_ui_destroy(ts_ui *);
void ts_ui_draw(ts_ui *, ts_Game *);
bool ts_ui_process_key(ts_ui *, ts_Game *);

#endif
