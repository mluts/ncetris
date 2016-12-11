#include "ncurses/ui.h"
#include <stdlib.h>
static void draw_board(ts_ui *ui, ts_Game *game)
{
ts_Pos pos;

  wclear(ui->board);
  box(ui->board, 0, 0);
  for(int y = 0; y < ui->boardHeight; y++)
  {
    wmove(ui->board, y+1, 1);
    for(int x = 0; x < ui->boardWidth; x++)
    {
      pos = (ts_Pos){y,x};

      if(ts_Board_get(game->board, &pos) != BOARD_EMPTY)
        waddch(ui->board, '#');
      else
        waddch(ui->board, ' ');
    }
  }

  wnoutrefresh(ui->board);
}

static void init_ncurses()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
}

ts_ui *ts_ui_new(int16_t boardWidth, int16_t boardHeight)
{
  ts_ui *ui = calloc(1, sizeof(ts_ui));
  if(ui != NULL)
  {
    init_ncurses();

    ui->boardWidth = boardWidth;
    ui->boardHeight = boardHeight;

    ui->board = newwin(
        boardHeight + 2, boardWidth + 2,
        0, 0
        );
  }

  return ui;
}

void ts_ui_destroy(ts_ui *ui)
{
  free(ui);
}

void ts_ui_draw(ts_ui *ui, ts_Game *game)
{
  draw_board(ui, game);
  doupdate();
}
