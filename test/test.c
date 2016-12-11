#include "ts_game.h"
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

int main()
{
  test_all_pieces_fit_to_empty_board();
  test_figure_is_on_board_on_start();
  test_figure_is_copied_to_board_after_failing();
  return 0;
}
