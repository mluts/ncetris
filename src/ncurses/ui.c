#include "ncurses/ui.h"
#include <stdlib.h>

#define COLS_PER_CELL 2
#define DRAW(win, ch) waddch(win, ch); waddch(win, ch)

static void draw_board(ts_ui *ui, ts_Game *game)
{
ts_Pos pos;
ts_BoardChar ch;

  wclear(ui->board);
  box(ui->board, 0, 0);
  for(int y = 0; y < ui->boardHeight; y++)
  {
    wmove(ui->board, y+1, 1);
    for(int x = 0; x < ui->boardWidth; x++)
    {
      pos = (ts_Pos){y,x};
      ch = ts_Board_get(game->board, &pos);

      if(ch != BOARD_EMPTY)
      {
        DRAW(ui->board, ' ' |
                        A_REVERSE |
                        COLOR_PAIR(BOARD_PIECE_TYPE(ch)));
      }
      else
      { DRAW(ui->board, ' '); }
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
  nodelay(stdscr, true);
  start_color();

  init_pair(TETROMINO_J, COLOR_GREEN, COLOR_BLACK);
  init_pair(TETROMINO_L, COLOR_CYAN, COLOR_BLACK);
  init_pair(TETROMINO_3, COLOR_RED, COLOR_BLACK);
  init_pair(TETROMINO_I, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TETROMINO_Z, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(TETROMINO_S, COLOR_BLUE, COLOR_BLACK);
  init_pair(TETROMINO_O, COLOR_WHITE, COLOR_BLACK);
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
        boardHeight + 2, boardWidth * COLS_PER_CELL + 2,
        1, 1
        );
  }

  return ui;
}

void ts_ui_destroy(ts_ui *ui)
{
  delwin(ui->board);
  endwin();
  free(ui);
}

void ts_ui_draw(ts_ui *ui, ts_Game *game)
{
  draw_board(ui, game);
  doupdate();
}

bool ts_ui_process_key(ts_ui *ui, ts_Game *game)
{
  switch(getch())
  {
    case KEY_LEFT:
      ts_Game_move(game, TS_LEFT);
      break;
    case KEY_RIGHT:
      ts_Game_move(game, TS_RIGHT);
      break;
    case KEY_UP:
      ts_Game_move(game, TS_ROTATE_CW);
      break;
    case KEY_DOWN:
      ts_Game_fall(game);
      return true;
      break;
  }
  return false;
}
