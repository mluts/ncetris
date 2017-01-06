#include "ncurses/ui.h"
#include <stdlib.h>

const int gravities[] = {150,125,100,75,50,40,30,20,15};

void getLevelScore(int linesremoved, int *level, int *score)
{
*score = 0;
*level = MINLEVEL;

  for(int i = 1; i <= linesremoved; i++) {
    if(i % LINES_PER_LEVEL == 0 && *level < MAXLEVEL)
    { (*level)++; }

    (*score) += (*level) * LEVEL_SCORE_MULTIPLIER;
  }
}

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

static void draw_next_falling(ts_ui *ui, ts_Game *game)
{
  ts_Piece *piece = ts_Piece_new(game->nextFalling->type);
  wclear(ui->nextFalling->win);
  box(ui->nextFalling->win, 0, 0);
  for(int n = 0; n < NUM_TETROMINO_SIZE; n++)
  {
    ts_Pos pos = ts_Piece_pos(piece, n);
    wmove(ui->nextFalling->win, pos.y + 2, 3 + pos.x * COLS_PER_CELL);
    DRAW(ui->nextFalling->win, ' ' | A_REVERSE | COLOR_PAIR(piece->type));
  }
  ts_Piece_destroy(piece);
  wnoutrefresh(ui->nextFalling->win);
}

static void draw_score(ts_ui *ui, ts_Game *game)
{
int score = 0, level = 0;
  if(ui->linesremoved != game->linesremoved) {
    getLevelScore(game->linesremoved, &level, &score);
    ui->scorenum = score;
    ui->level = level;
    ui->linesremoved = game->linesremoved;
  } else {
    score = ui->scorenum;
    level = ui->level;
  }

  wclear(ui->score->win);
  box(ui->score->win, 0, 0);
  mvwprintw(ui->score->win, 1, 2, "Level: %d", level);
  mvwprintw(ui->score->win, 2, 2, "Score: %d", score);
  wnoutrefresh(ui->score->win);
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

    ui->board = ts_ui_win_new(
        boardHeight + 2, boardWidth * COLS_PER_CELL + 2,
        1, 1
        );

    ui->nextFalling = ts_ui_win_new(
        NUM_TETROMINO_SIZE + 3,
        (NUM_TETROMINO_SIZE * COLS_PER_CELL) + 4,
        1, ui->board->width + 1
        );

    ui->score = ts_ui_win_new(
        4,
        18,
        ui->nextFalling->height + 1,
        ui->board->width + 1
        );

    ui->exitRequested = false;
    ui->pause = false;

    ui->linesremoved = 0;
    ui->level = MINLEVEL;
    ui->scorenum = 0;
  }

  return ui;
}

void ts_ui_destroy(ts_ui *ui)
{
  ts_ui_win_destroy(ui->board);
  ts_ui_win_destroy(ui->nextFalling);
  ts_ui_win_destroy(ui->score);
  endwin();
  free(ui);
}

void ts_ui_draw(ts_ui *ui, ts_Game *game)
{
  draw_board(ui, game);
  draw_next_falling(ui, game);
  draw_score(ui, game);
  doupdate();
}

bool ts_ui_process_key(ts_ui *ui, ts_Game *game)
{
int c = getch();

  if(c == 'c')
    ui->pause = !ui->pause;

  if(ui->pause)
    return false;

  switch(c)
  {
    case 'q':
      ui->exitRequested = true;
      break;
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
