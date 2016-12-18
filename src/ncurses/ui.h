#ifndef _NCURSES_UI_H
#define _NCURSES_UI_H
#include <ncurses.h>
#include "ts_game.h"

typedef struct {
  WINDOW *win;
  int16_t width, height, y, x;
} ts_ui_win;

typedef struct {
  ts_ui_win *board;
  ts_ui_win *nextFailing;
  int16_t boardWidth, boardHeight;
} ts_ui;

ts_ui *ts_ui_new(int16_t boardWidth, int16_t boardHeight);
void ts_ui_destroy(ts_ui *);
void ts_ui_draw(ts_ui *, ts_Game *);
bool ts_ui_process_key(ts_ui *, ts_Game *);

ts_ui_win *ts_ui_win_new(int16_t h, int16_t w, int16_t y, int16_t x);
void ts_ui_win_destroy(ts_ui_win *);

#endif
