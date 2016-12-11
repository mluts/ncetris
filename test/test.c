#include "ts_game.h"
#include "ts_loop.h"
#include <assert.h>
#include <stdlib.h>

const int w = 30, h = 30;

void test_all_pieces_fit_to_empty_board()
{
  ts_Board *board = ts_Board_new(w, h);
  ts_Piece *piece = ts_Piece_new(RANDOM_TETROMINO);
  assert(ts_Board_piecefits(board, piece) && "Piece should fit to empty board");

  ts_Board_destroy(board);
  ts_Piece_destroy(piece);
}

void test_figure_is_on_board_on_start()
{
  ts_Game *game = ts_Game_new(w, h);
  ts_Game_fall(game);
  for(int n = 0; n < NUM_TETROMINO_SIZE; n++)
  {
    ts_Pos pos = ts_Piece_pos(game->failing, n);
    assert(ts_Board_get(game->board, &pos) != BOARD_EMPTY && "Piece should be present on board");
  }
  ts_Game_destroy(game);
}

void test_figure_is_copied_to_board_after_failing()
{
  ts_Pos pos[4];

  ts_Game *game = ts_Game_new(w, h);
  while(ts_Board_piecefits(game->board, game->failing))
    ts_Piece_move(game->failing, 1, 0);
  ts_Piece_move(game->failing, -1, 0);

  for(int n = 0; n < NUM_TETROMINO_SIZE; n++)
    pos[n] = ts_Piece_pos(game->failing, n);

  ts_Game_fall(game);
  ts_Game_fall(game);
  ts_Game_fall(game);

  for(int n = 0; n < NUM_TETROMINO_SIZE; n++)
    assert(ts_Board_get(game->board, &pos[n]) != BOARD_EMPTY && "Board should contain old piece");

  ts_Game_destroy(game);
}

void test_loop_increments_frames()
{
int frames = 1 + rand() % 30, i = frames;
  ts_GameLoop *loop = ts_GameLoop_new((struct timeval){0, 1});
  while(i > 0)
  {
    ts_GameLoop_startFrame(loop);
    ts_GameLoop_stopFrame(loop);
    i--;
  }
  assert(ts_GameLoop_getframes(loop) == frames && "Frames should increment");
  ts_GameLoop_destroy(loop);
}

void test_game_increments_lines_removed()
{
int16_t lines = 1 + rand() % 3;
  ts_Game *game = ts_Game_new(w, h);
  for(int y = h-1; y >= h-lines; y--)
    for(int x = 0; x < w; x++)
      ts_Board_set(game->board, &(ts_Pos){y,x}, BOARD_PIECE(game->failing));

  assert(ts_Game_getlinesremoved(game) == 0 && "Initially linesremoved should be 0");
  ts_Game_fall(game);
  assert(ts_Game_getlinesremoved(game) == lines && "linesremoved should be incremented for each removed line");

  ts_Game_destroy(game);
}

int main()
{
  test_all_pieces_fit_to_empty_board();
  test_figure_is_on_board_on_start();
  test_figure_is_copied_to_board_after_failing();
  test_loop_increments_frames();
  test_game_increments_lines_removed();
  return 0;
}
