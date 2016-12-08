#include "ts_piece.h"
#include <stdlib.h>
#include <string.h>

#define Y(piece) (piece->position.y)
#define X(piece) (piece->position.x)

ts_Piece *ts_Piece_new()
{
  ts_Piece *piece = calloc(1, sizeof(ts_Piece));
  return piece;
}

void ts_Piece_destroy(ts_Piece *piece)
{ free(piece); }

void ts_Piece_setshape(ts_Piece *piece, ts_PieceShape shape)
{
  piece->shape = shape;
  piece->rotation = 0;
}

void ts_Piece_setposition(ts_Piece *piece, const ts_Coord coord)
{ piece->position = coord; }

void J_coords(ts_Piece *piece, ts_Coord *coord, uint8_t length)
{
  /*
   *  #
   *  #
   * ##
   */
  ts_Coord J0[] = {
    {Y(piece), X(piece)+1},
    {Y(piece)+1, X(piece)+1},
    {Y(piece)+2, X(piece)},
    {Y(piece)+2, X(piece)+1},
  };

  /*
   * #  
   * ###
   */
  ts_Coord J1[] = {
    {Y(piece), X(piece)},
    {Y(piece)+1, X(piece)},
    {Y(piece)+1, X(piece)+1},
    {Y(piece)+1, X(piece)+2},
  };

  /*
   * ##
   * #
   * #
   */
  ts_Coord J2[] = {
    {Y(piece), X(piece)},
    {Y(piece), X(piece)+1},
    {Y(piece)+1, X(piece)},
    {Y(piece)+2, X(piece)},
  };

  /*
   * ###
   *   #
   */
  ts_Coord J3[] = {
    {Y(piece), X(piece)},
    {Y(piece), X(piece)+1},
    {Y(piece), X(piece)+2},
    {Y(piece)+1, X(piece)+2},
  };

  switch(piece->rotation % 4)
  {
    case 0:
      memcpy(coord, J0, length * sizeof(ts_Coord));
      break;
    case 1:
      memcpy(coord, J1, length * sizeof(ts_Coord));
      break;
    case 2:
      memcpy(coord, J2, length * sizeof(ts_Coord));
      break;
    case 3:
      memcpy(coord, J3, length * sizeof(ts_Coord));
      break;
  }
}

void Z_coord(ts_Piece *piece, ts_Coord *coord, uint8_t length)
{
  /*
   * ##
   *  ##
   */
  ts_Coord Z0[] = {
    {Y(piece), X(piece)},
    {Y(piece), X(piece)+1},
    {Y(piece)+1, X(piece)+1},
    {Y(piece)+1, X(piece)+2},
  };

  /*
   *  #
   * ##
   * #
   */
  ts_Coord Z1[] = {
    {Y(piece), X(piece)+1},
    {Y(piece)+1, X(piece)},
    {Y(piece)+1, X(piece)+1},
    {Y(piece)+2, X(piece)},
  };

  switch(piece->rotation % 2) {
    case 0:
      memcpy(coord, Z0, length * sizeof(ts_Coord));
      break;
    case 1:
      memcpy(coord, Z1, length * sizeof(ts_Coord));
      break;
  }
}

void L_coord(ts_Piece *piece, ts_Coord *coord, uint8_t length)
{
  /*
   * #
   * #
   * ##
   */
  ts_Coord L0[] = {
    {Y(piece), X(piece)},
    {Y(piece)+1, X(piece)},
    {Y(piece)+2, X(piece)},
    {Y(piece)+2, X(piece)+1},
  };

  /*
   * ###
   * #
   */
  ts_Coord L1[] = {
    {Y(piece), X(piece)},
    {Y(piece), X(piece)+1},
    {Y(piece), X(piece)+2},
    {Y(piece)+1, X(piece)},
  };

  /*
   * ##
   *  #
   *  #
   */
  ts_Coord L2[] = {
    {Y(piece), X(piece)},
    {Y(piece), X(piece)+1},
    {Y(piece)+1, X(piece)+1},
    {Y(piece)+2, X(piece)+1},
  };

  /*
   *   #
   * ###
   */
  ts_Coord L3[] = {
    {Y(piece), X(piece)+2},
    {Y(piece)+1, X(piece)},
    {Y(piece)+1, X(piece)+1},
    {Y(piece)+1, X(piece)+2},
  };

  switch(piece->rotation % 4) {
    case 0:
      memcpy(coord, L0, length * sizeof(ts_Coord));
      break;
    case 1:
      memcpy(coord, L1, length * sizeof(ts_Coord));
      break;
    case 2:
      memcpy(coord, L2, length * sizeof(ts_Coord));
      break;
    case 3:
      memcpy(coord, L3, length * sizeof(ts_Coord));
      break;
  }
}

void S_coord(ts_Piece *piece, ts_Coord *coord, uint8_t length)
{
  /*
   *  ##
   * ##
   */
  ts_Coord S0[] = {
    {Y(piece), X(piece)+1},
    {Y(piece), X(piece)+2},
    {Y(piece)+1, X(piece)},
    {Y(piece)+1, X(piece)+1},
  };

  /*
   * # 
   * ##
   *  #
   */
  ts_Coord S1[] = {
    {Y(piece), X(piece)},
    {Y(piece)+1, X(piece)},
    {Y(piece)+1, X(piece)+1},
    {Y(piece)+2, X(piece)+1},
  };

  switch(piece->rotation % 2) {
    case 0:
      memcpy(coord, S0, length * sizeof(ts_Coord));
      break;
    case 1:
      memcpy(coord, S1, length * sizeof(ts_Coord));
      break;
  }
}

void LINE_coord(ts_Piece *piece, ts_Coord *coord, uint8_t length)
{
  /*
   * #
   * #
   * #
   * #
   */
  ts_Coord LINE0[] = {
    {Y(piece), X(piece)},
    {Y(piece)+1, X(piece)},
    {Y(piece)+2, X(piece)},
    {Y(piece)+3, X(piece)},
  };

  /*
   * ####
   */
  ts_Coord LINE1[] = {
    {Y(piece), X(piece)},
    {Y(piece), X(piece)+1},
    {Y(piece), X(piece)+2},
    {Y(piece), X(piece)+3},
  };

  switch(piece->rotation % 2) {
    case 0:
      memcpy(coord, LINE0, length * sizeof(ts_Coord));
      break;
    case 1:
      memcpy(coord, LINE1, length * sizeof(ts_Coord));
      break;
  }
}

void CUBE_coord(ts_Piece *piece, ts_Coord *coord, uint8_t length)
{
  /*
   * ##
   * ##
   */
  ts_Coord CUBE[] = {
    {Y(piece), X(piece)},
    {Y(piece), X(piece)+1},
    {Y(piece)+1, X(piece)},
    {Y(piece)+1, X(piece)+1},
  };

  memcpy(coord, CUBE, length * sizeof(ts_Coord));
}

void ts_Piece_getcoords(ts_Piece *piece, ts_Coord *coord, uint8_t length)
{
  switch(piece->shape) {
    case J:
      J_coords(piece, coord, length);
      break;
    case Z:
      Z_coord(piece, coord, length);
      break;
    case L:
      L_coord(piece, coord, length);
      break;
    case S:
      S_coord(piece, coord, length);
      break;
    case LINE:
      LINE_coord(piece, coord, length);
      break;
    case CUBE:
      CUBE_coord(piece, coord, length);
      break;
  }
}
