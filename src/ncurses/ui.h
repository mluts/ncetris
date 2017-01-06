#ifndef _NCURSES_UI_H
#define _NCURSES_UI_H
#include <ncurses.h>
#include "ts_game.h"

extern const int gravities[];

#define COLS_PER_CELL 2
#define DRAW(win, ch) waddch(win, ch); waddch(win, ch)
#define LINES_PER_LEVEL 10
#define LEVEL_SCORE_MULTIPLIER 40
#define MINLEVEL 1
#define MAXLEVEL 10
#define GRAVITY_PER_LEVEL(l) gravities[l-1]

typedef struct {
  WINDOW *win;
  int16_t width, height, y, x;
} ts_ui_win;

typedef struct {
  ts_ui_win *board;
  ts_ui_win *nextFalling;
  ts_ui_win *score;
  int16_t boardWidth, boardHeight;
  int32_t linesremoved, scorenum, level;
  bool exitRequested, pause;
} ts_ui;

ts_ui *ts_ui_new(int16_t boardWidth, int16_t boardHeight);
void ts_ui_destroy(ts_ui *);
void ts_ui_draw(ts_ui *, ts_Game *);
bool ts_ui_process_key(ts_ui *, ts_Game *);

ts_ui_win *ts_ui_win_new(int16_t h, int16_t w, int16_t y, int16_t x);
void ts_ui_win_destroy(ts_ui_win *);

#endif
