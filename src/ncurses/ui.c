#include "ncurses/ui.h"
#include <stdlib.h>

#define COLS_PER_CELL 2
#define DRAW(win, ch) waddch(win, ch); waddch(win, ch)

static void draw_board(ts_ui *ui, ts_Game *game)
{
ts_Pos pos;
ts_BoardChar ch;

  wclear(ui->board->win);
  box(ui->board->win, 0, 0);
  for(int y = 0; y < ui->boardHeight; y++)
  {
    wmove(ui->board->win, y+1, 1);
    for(int x = 0; x < ui->boardWidth; x++)
    {
      pos = (ts_Pos){y,x};
      ch = ts_Board_get(game->board, &pos);

      if(ch != BOARD_EMPTY)
      {
        DRAW(ui->board->win, ' ' |
                        A_REVERSE |
                        COLOR_PAIR(BOARD_PIECE_TYPE(ch)));
      }
      else
      { DRAW(ui->board->win, ' '); }
    }
  }

  wnoutrefresh(ui->board->win);
}

static void draw_next_failing(ts_ui *ui, ts_Game *game)
{
  ts_Piece *piece = ts_Piece_new(game->failing->type);
  wclear(ui->nextFailing->win);
  box(ui->nextFailing->win, 0, 0);
  for(int n = 0; n < NUM_TETROMINO_SIZE; n++)
  {
    ts_Pos pos = ts_Piece_pos(piece, n);
    wmove(ui->nextFailing->win, pos.y + 2, 3 + pos.x * COLS_PER_CELL);
    DRAW(ui->nextFailing->win, ' ' | A_REVERSE | COLOR_PAIR(piece->type));
  }
  ts_Piece_destroy(piece);
  wnoutrefresh(ui->nextFailing->win);
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
int boardWindowHeight, boardWindowWidth;

  ts_ui *ui = calloc(1, sizeof(ts_ui));
  if(ui != NULL)
  {
    init_ncurses();

    ui->boardWidth = boardWidth;
    ui->boardHeight = boardHeight;

    boardWindowHeight = boardHeight + 2;
    boardWindowWidth = boardWidth * COLS_PER_CELL + 2;

    ui->board = ts_ui_win_new(
        boardWindowHeight, boardWindowWidth,
        1, 1
        );

    ui->nextFailing = ts_ui_win_new(
        NUM_TETROMINO_SIZE + 3,
        (NUM_TETROMINO_SIZE * COLS_PER_CELL) + 4,
        1, boardWindowWidth + 1
        );
  }

  return ui;
}

void ts_ui_destroy(ts_ui *ui)
{
  ts_ui_win_destroy(ui->board);
  ts_ui_win_destroy(ui->nextFailing);
  endwin();
  free(ui);
}

void ts_ui_draw(ts_ui *ui, ts_Game *game)
{
  draw_board(ui, game);
  draw_next_failing(ui, game);
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

ts_ui_win *ts_ui_win_new(int16_t h, int16_t w, int16_t y, int16_t x)
{
  ts_ui_win *win = calloc(1, sizeof(ts_ui_win));
  if(win != NULL)
  {
    win->win = newwin(h, w, y, x);
    win->width = w;
    win->height = h;
    win->y = y;
    win->x = x;
  }
  return win;
}

void ts_ui_win_destroy(ts_ui_win *win)
{
  delwin(win->win);
  free(win);
}
