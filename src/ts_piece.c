#include "ts_piece.h"
#include "ts_pos.h"
#include <stdint.h>
#include <stdlib.h>

const ts_Pos TETROMINOS[NUM_TETROMINOS][NUM_ORIENTATIONS][NUM_TETROMINO_SIZE] = {
  {
    /*
     *  #
     *  #
     * ##
     */
    {{0,1},{1,1},{2,1},{2,0}},
    /*
     * #
     * ###
     */
    {{0,0},{1,0},{1,1},{1,2}},
    /*
     * ##
     * #
     * #
     */
    {{0,0},{0,1},{1,0},{2,0}},
    /*
     * ###
     *   #
     */
    {{0,0},{0,1},{0,2},{1,2}}
  },
  {
    /*
     * #
     * #
     * ##
     */
    {{0,0},{1,0},{2,0},{2,1}},
    /*
     * ###
     * #
     */
    {{0,0},{0,1},{0,2},{1,0}},
    /*
     * ##
     *  #
     *  #
     */
    {{0,0},{0,1},{1,1},{2,1}},
    /*
     *   #
     * ###
     */
    {{0,2},{1,0},{1,1},{1,2}}
  },
  {
    /*
     *  #
     * ###
     */
    {{0,1},{1,0},{1,1},{1,2}},
    /*
     * #
     * ##
     * #
     */
    {{0,0},{1,0},{2,0},{1,1}},
    /*
     * ###
     *  #
     */
    {{0,0},{0,1},{0,2},{1,1}},
    /*
     *  #
     * ##
     *  #
     */
    {{0,1},{1,0},{1,1},{2,1}}
  },
  {
    /*
     * ####
     */
    {{0,0},{0,1},{0,2},{0,3}},
    /*
     * #
     * #
     * #
     * #
     */
    {{0,0},{1,0},{2,0},{3,0}},
    /*
     * ####
     */
    {{0,0},{0,1},{0,2},{0,3}},
    /*
     * #
     * #
     * #
     * #
     */
    {{0,0},{1,0},{2,0},{3,0}}
  },
  {
    /*
     * ##
     *  ##
     */
    {{0,0},{0,1},{1,1},{1,2}},
    /*
     *  #
     * ##
     * #
     */
    {{0,1},{1,0},{1,1},{2,0}},
    /*
     * ##
     *  ##
     */
    {{0,0},{0,1},{1,1},{1,2}},
    /*
     *  #
     * ##
     * #
     */
    {{0,1},{1,0},{1,1},{2,0}},
  },
  {
    /*
     *  ##
     * ##
     */
    {{0,1},{0,2},{1,0},{1,1}},
    /*
     * #
     * ##
     *  #
     */
    {{0,0},{1,0},{1,1},{2,1}},
    /*
     *  ##
     * ##
     */
    {{0,1},{0,2},{1,0},{1,1}},
    /*
     * #
     * ##
     *  #
     */
    {{0,0},{1,0},{1,1},{2,1}},
  },
  {
    /*
     * ##
     * ##
     */
    {{0,0},{0,1},{1,0},{1,1}},
    /*
     * ##
     * ##
     */
    {{0,0},{0,1},{1,0},{1,1}},
    /*
     * ##
     * ##
     */
    {{0,0},{0,1},{1,0},{1,1}},
    /*
     * ##
     * ##
     */
    {{0,0},{0,1},{1,0},{1,1}},
  }
};

ts_Piece *ts_Piece_new(int8_t type)
{
  ts_Piece *piece = calloc(1, sizeof(ts_Piece));
  if(piece != NULL)
  {
    piece->type = type % NUM_TETROMINOS;
  }
  return piece;
}

void ts_Piece_destroy(ts_Piece *piece)
{ free(piece); }

void ts_Piece_rotate(ts_Piece *piece, int8_t direction)
{
  if(direction < 0)
    piece->orientation--;
  else
    if(direction > 0)
      piece->orientation++;

  piece->orientation %= NUM_ORIENTATIONS;
}

void ts_Piece_move(ts_Piece *piece, int8_t dy, int8_t dx)
{
  if(dy < 0)
    piece->pos.y--;
  else if(dy > 0)
    piece->pos.y++;

  if(dx < 0)
    piece->pos.x--;
  else if(dx > 0)
    piece->pos.x++;
}

ts_Pos ts_Piece_pos(const ts_Piece *piece, int8_t n)
{
ts_Pos tetromino = TETROMINOS[piece->type][piece->orientation][n];

  return (ts_Pos){
    piece->pos.y + tetromino.y,
    piece->pos.x + tetromino.x
  };
}
