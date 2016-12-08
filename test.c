#include "ts_piece.h"
#include "ts_game.h"
#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void assert_timeval_subtract_result(struct timeval x, struct timeval y, struct timeval expected, int expected_negative)
{
  struct timeval result;
  int negative;
  memset(&result, 0, sizeof(result));
  negative = timeval_subtract(&x, &y, &result);

  printf("Comparing %ld with %ld\n",
         result.tv_sec, expected.tv_sec);
  ASSERT_EQUAL(result.tv_sec, expected.tv_sec);

  printf("Comparing %ld with %ld\n",
         result.tv_usec, expected.tv_usec);
  ASSERT_EQUAL(result.tv_usec, expected.tv_usec);

  printf("Comparing %d with %d\n",
         expected_negative, negative);
  ASSERT_EQUAL(expected_negative, negative);
}

void test_timeval_subtract()
{
  assert_timeval_subtract_result(
    (struct timeval) {3, 1000},
    (struct timeval) {2, 3000},
    (struct timeval) {0, 1000000-2000},
    0
  );

  assert_timeval_subtract_result(
    (struct timeval) {3, 1000},
    (struct timeval) {2, 1000},
    (struct timeval) {1, 0},
    0
  );

  assert_timeval_subtract_result(
    (struct timeval) {2, 1000},
    (struct timeval) {1, 500},
    (struct timeval) {1, 500},
    0
  );

  assert_timeval_subtract_result(
    (struct timeval) {2, 1000},
    (struct timeval) {2, 1000},
    (struct timeval) {0, 0},
    0
  );

  assert_timeval_subtract_result(
    (struct timeval) {1, 1000},
    (struct timeval) {2, 1000},
    (struct timeval) {1, 0},
    1
  );

  assert_timeval_subtract_result(
    (struct timeval) {1, 1000},
    (struct timeval) {1, 1500},
    (struct timeval) {0, 500},
    1
  );
}

int main()
{
  test_piece_initial_values();
  test_Z_piece_coords();
  test_timeval_subtract();
  return 0;
}
