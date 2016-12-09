#include "ts_loop.h"
#include "ts_game.h"
#include <ncurses.h>

ts_Game *game;
ts_GameLoop loop;

void draw_game(uint8_t y, uint8_t x)
{
  mvaddch(y, x, '#');
}

void framemove()
{
  ts_Game_move(game);
}

void framedraw()
{
  erase();
  ts_Game_draw(game, draw_game);
  refresh();
}

int wwidth()
{
  return tigetnum("cols");
}

int wheight()
{
  return tigetnum("lines");
}

int main()
{
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);

  game = ts_Game_new(wwidth(), wheight()/3);
  loop = ts_GameLoop_new(
      (struct timeval){0, 16000},
      (struct timeval){1, 0}
  );

  while(!game->finished) {
    ts_GameLoop_move(&loop, framemove);
    ts_GameLoop_draw(&loop, framedraw);
  }

  endwin();
}
