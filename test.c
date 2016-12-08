#include "ts_piece.h"
#include "ts_game.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define ASSERT_EQUAL(A, B) (assert((A) == (B) && "Expected " #A "to equal " #B))

void test_Z_piece_coords()
{
ts_Coord coord = {rand() % 10, rand() % 10};
ts_Coord coords[16] = {0};

  ts_Piece *piece = ts_Piece_new(Z);
  ts_Piece_setposition(piece, coord);
  ts_Piece_getcoords(piece, coords, 16);

  ASSERT_EQUAL(coords[0].y, coord.y);
  ASSERT_EQUAL(coords[0].x, coord.x);
  ASSERT_EQUAL(coords[1].y, coord.y);
  ASSERT_EQUAL(coords[1].x, coord.x+1);
  ASSERT_EQUAL(coords[2].y, coord.y+1);
  ASSERT_EQUAL(coords[2].x, coord.x+1);
  ASSERT_EQUAL(coords[3].y, coord.y+1);
  ASSERT_EQUAL(coords[3].x, coord.x+2);

  ts_Piece_destroy(piece);
}

void test_piece_initial_values()
{
  ts_Piece *piece = ts_Piece_new(Z);
  ASSERT_EQUAL(piece->rotation, 0);
  ASSERT_EQUAL(piece->position.y, 0);
  ASSERT_EQUAL(piece->position.x, 0);
  ts_Piece_destroy(piece);
}

int main()
{
  test_piece_initial_values();
  test_Z_piece_coords();
  return 0;
}
