#include "ts_board.h"
#include <stdlib.h>

static inline ts_PosNumber boardindex(const ts_Board *board, const ts_Pos *pos)
{
  return pos->x + board->width * pos->y;
}

static inline bool within_bounds(const ts_Board *board, const ts_Pos *pos)
{
  return pos->y > 0 && pos->y < board->height &&
         pos->x > 0 && pos->x < board->width;
}

ts_Board *ts_Board_new(ts_BoardDimension width, ts_BoardDimension height)
{
  ts_Board *board = calloc(1, sizeof(ts_Board));
  if(board != NULL) {
    board->width = width;
    board->height = height;
    board->board = calloc(width*height, sizeof(ts_BoardChar));
  }
  return board;
}

void ts_Board_destroy(ts_Board *board)
{
  free(board->board);
  free(board);
}

void ts_Board_put_piece(ts_Board *board, const ts_Piece *piece)
{
  for(int n = 0; n < NUM_TETROMINO_SIZE; n++)
    ts_Board_set(board, &PIECE_POS(piece, n), BOARD_PRESENT);
}

void ts_Board_remove_piece(ts_Board *board, const ts_Piece *piece)
{
  for(int pos = 0; pos < NUM_TETROMINO_SIZE; pos++)
    ts_Board_unset(board, &PIECE_POS(piece, pos));
}

void ts_Board_set(ts_Board *board, const ts_Pos *pos, ts_BoardChar value)
{
  if(within_bounds(board, pos))
    board->board[boardindex(board, pos)] = value;
}

void ts_Board_unset(ts_Board *board, const ts_Pos *pos)
{
  if(within_bounds(board, pos))
    board->board[boardindex(board, pos)] = BOARD_EMPTY;
}

bool ts_Board_piecefits(const ts_Board *board, const ts_Piece *piece)
{
ts_Pos pos;
int n;

  for(n = 0, pos = PIECE_POS(piece, n); n < NUM_TETROMINO_SIZE; n++, pos = PIECE_POS(piece, n))
    if(!within_bounds(board, &pos) ||
        board->board[boardindex(board, &pos)] != BOARD_EMPTY)
      return false;
  return true;
}

ts_BoardChar ts_Board_get(const ts_Board *board, const ts_Pos *pos)
{ return board->board[boardindex(board, pos)]; }
