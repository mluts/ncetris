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
  INFO("--testing Z piece coords");
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
  INFO("--testing piece default values");
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
  INFO("--testing timeval subtraction");
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

void test_coord_collision()
{
  ASSERT_EQUAL(
      true,
      ts_Coord_downCollision(
        &(ts_Coord){0,1},
        &(ts_Coord){1,1}
      )
  );

  ASSERT_EQUAL(
      false,
      ts_Coord_downCollision(
        &(ts_Coord){0,0},
        &(ts_Coord){0,1}
      )
  );

  ASSERT_EQUAL(
      false,
      ts_Coord_downCollision(
        &(ts_Coord){0,1},
        &(ts_Coord){2,1}
      )
  );
}

void test_game_piece_collision()
{
INFO("--Testing game piece collision");
  int w = 20, h = 20;
  ts_Game *game = ts_Game_new(w,h);
  game->piece = ts_Piece_new(J);

  ts_Piece_setposition(game->piece, (ts_Coord){17, 10});

  INFO("  Expecting down collision");
  ASSERT_EQUAL(
      true,
      ts_Game_pieceDownCollision(game)
      );

  ts_Piece_setposition(game->piece, (ts_Coord){15, 10});

  INFO("  Expecting no down collision");
  ASSERT_EQUAL(
      false,
      ts_Game_pieceDownCollision(game)
      );

  ts_Game_destroy(game);
}

void assert_timeval_add_result(
    const struct timeval *x,
    const struct timeval *y,
    const struct timeval *expected
    )
{
struct timeval result;
  timeval_add(x, y, &result);
  ASSERT_EQUAL(result.tv_sec, expected->tv_sec);
  ASSERT_EQUAL(result.tv_usec, expected->tv_usec);
}

void test_timeval_add()
{
  assert_timeval_add_result(
    &(struct timeval){0, 100},
    &(struct timeval){0, 100},
    &(struct timeval){0, 200}
  );

  assert_timeval_add_result(
    &(struct timeval){0, 500000},
    &(struct timeval){1, 500100},
    &(struct timeval){2, 100}
  );
}

void test_piece_rotation()
{
  ts_Piece *piece = ts_Piece_new(LINE);
  ASSERT_EQUAL(piece->rotation, 0);

  ts_Piece_rotate_cw(piece);
  ASSERT_EQUAL(piece->rotation, 1);

  ts_Piece_rotate_cw(piece);
  ASSERT_EQUAL(piece->rotation, 2);

  ts_Piece_rotate_cw(piece);
  ASSERT_EQUAL(piece->rotation, 3);

  ts_Piece_rotate_cw(piece);
  ASSERT_EQUAL(piece->rotation, 0);

  ts_Piece_rotate_cw(piece);
  ASSERT_EQUAL(piece->rotation, 1);

  ts_Piece_destroy(piece);
}

void test_piece_left_collision()
{
  ASSERT_EQUAL(
      true,
      ts_Coord_leftCollision(
        &(ts_Coord){ 10, 10 },
        &(ts_Coord){ 10, 9 }
        )
      );

  ASSERT_EQUAL(
      false,
      ts_Coord_leftCollision(
        &(ts_Coord){ 10, 11 },
        &(ts_Coord){ 10, 9 }
        )
      );

  ASSERT_EQUAL(
      true,
      ts_Coord_leftCollision(
        &(ts_Coord){ 10, 1 },
        &(ts_Coord){ 10, 0 }
        )
      );

  ASSERT_EQUAL(
      false,
      ts_Coord_leftCollision(
        &(ts_Coord){ 10, 10 },
        &(ts_Coord){ 9, 9 }
        )
      );
}

int main()
{
  test_piece_initial_values();
  test_Z_piece_coords();
  test_timeval_subtract();
  test_timeval_add();
  test_coord_collision();
  test_game_piece_collision();
  test_piece_rotation();
  test_piece_left_collision();
  return 0;
}
