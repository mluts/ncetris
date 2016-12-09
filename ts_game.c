#include "ts_game.h"
#include "ts_piece.h"
#include <stdlib.h>

ts_Game *ts_Game_new(uint8_t w, uint8_t h)
{
  ts_Game *game = calloc(1, sizeof(ts_Game));
  if(game != NULL) {
    game->width = w;
    game->height = h;
    game->piece = NULL;
    game->dots = calloc(w*h, sizeof(uint8_t));
  }
  return game;
}

/*! Private */
uint16_t dotindex(ts_Game *game, uint8_t y, uint8_t x)
{
  return x + y * game->width;
}

void ts_Game_setdot(ts_Game *game, uint8_t y, uint8_t x, uint8_t val)
{
  game->dots[dotindex(game, y, x)] = val;
}

uint8_t ts_Game_getdot(ts_Game *game, uint8_t y, uint8_t x)
{
  return game->dots[dotindex(game, y, x)];
}

void ts_Game_freezepiece(ts_Game *game)
{
  ts_Coord coords[16];
  int size;
  size = ts_Piece_getcoords(game-> piece, coords, 16);
  for(int i = 0; i < size; i++)
    ts_Game_setdot(game, coords[i].y, coords[i].x, 1);
  game->piece = NULL;
}

void ts_Game_spawnpiece(ts_Game *game)
{
  if(game->piece != NULL) {
    ts_Game_freezepiece(game);
  }
  game->piece = ts_Piece_new(Z);
}

void ts_Game_destroy(ts_Game *game)
{
  free(game->dots);
  free(game->piece);
  free(game);
}

void ts_Game_draw(ts_Game *game, ts_Game_drawfn fn)
{
  for(int y = 0; y < game->height; y++)
    for(int x = 0; x < game->width; x++)
      if(ts_Game_getdot(game, y, x) > 0)
        fn(y, x);

  if(game->piece != NULL)
    ts_Piece_draw(game->piece, fn);
}

bool ts_Game_pieceDownCollision(ts_Game *game)
{
ts_Coord coords[16];
int size;

  if(game->piece == NULL) { return false; }

  size = ts_Piece_getcoords(game->piece, coords, 16);

  for(int i = 0; i < size; i++)
    if(coords[i].y+1 == game->height ||
       ts_Game_getdot(game, coords[i].y+1, coords[i].x) > 0)
      return true;

  return false;
}

bool ts_Game_pieceUpCollision(ts_Game *game)
{
ts_Coord coords[16];
int size;

  if(game->piece == NULL) { return false; }

  size = ts_Piece_getcoords(game->piece, coords, 16);

  if(ts_Game_pieceDownCollision(game))
    for(int i = 0; i < size; i++)
      if(coords[i].y - 1 < 0)
        return true;

  return false;
}

void ts_Game_move(ts_Game *game)
{
  if(game->finished) { return; }

  if(game->piece == NULL || ts_Game_pieceDownCollision(game)) {
    ts_Game_spawnpiece(game);

    if(ts_Game_pieceUpCollision(game))
    {
      game->finished = true;
    }
  } else {
    ts_Piece_setposition(
        game->piece,
        (ts_Coord){
          game->piece->position.y+1,
          game->piece->position.x 
        }
    );
  }
}

bool ts_Game_pieceLeftCollision(ts_Game *game)
{
  ts_Coord coord[16];
int size;

  if(game->piece == NULL) { return false; }

  size = ts_Piece_getcoords(game->piece, coord, 16);
  for(int i = 0; i < size; i++)
    if(coord[i].x-1 < 0 ||
        ts_Game_getdot(game, coord[i].y, coord[i].x-1) > 0)
      return true;

  return false;
}

bool ts_Game_pieceRightCollision(ts_Game *game)
{
  ts_Coord coord[16];
int size;

  if(game->piece == NULL) { return false; }

  size = ts_Piece_getcoords(game->piece, coord, 16);
  for(int i = 0; i < size; i++)
    if(coord[i].x+1 >= game->width ||
        ts_Game_getdot(game, coord[i].y, coord[i].x+1) > 0)
      return true;

  return false;
}
