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
    game->frozenPieces = calloc(MAX_PIECES, sizeof(void*));
    game->frozenPiecesCount = 0;
  }
  return game;
}

void ts_Game_freezepiece(ts_Game *game)
{
  game->frozenPieces[game->frozenPiecesCount++] = game->piece;
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
  free(game->frozenPieces);
  free(game->piece);
  free(game);
}

void ts_Game_draw(ts_Game *game, ts_Game_drawfn fn)
{
  for(int i = 0; i < game->frozenPiecesCount; i++)
  { ts_Piece_draw(game->frozenPieces[i], fn); }

  if(game->piece != NULL)
  { ts_Piece_draw(game->piece, fn); }
}

bool ts_Game_pieceDownCollision(ts_Game *game)
{
ts_Coord coords[16],
         frozenCoords[16],
         bottomCoords[game->width];
int size, frozenSize;

  if(game->piece == NULL) { return false; }

  size = ts_Piece_getcoords(game->piece, coords, 16);
  ts_Game_getBottomBorderCoords(game, bottomCoords, game->width);
  if(ts_Coords_downCollision(coords, size, bottomCoords, game->width))
    return true;

  for(int i = 0; i < game->frozenPiecesCount; i++)
  {
    frozenSize = ts_Piece_getcoords(game->frozenPieces[i], frozenCoords, 16);
    if(ts_Coords_downCollision(coords, size, frozenCoords, frozenSize))
      return true;
  }

  return false;
}

bool ts_Game_pieceUpCollision(ts_Game *game)
{
ts_Coord coords[16],
         topCoords[game->width];
int size;

  if(game->piece == NULL) { return false; }

  size = ts_Piece_getcoords(game->piece, coords, 16);
  ts_Game_getTopBorderCoords(game, topCoords, game->width);

  if(ts_Coords_downCollision(topCoords, game->width, coords, size) &&
      ts_Game_pieceDownCollision(game))
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

void ts_Game_getBottomBorderCoords(ts_Game *game, ts_Coord *coords, uint8_t length)
{
int i = 0;
  for(i = 0; i < game->width && i < length; i++)
  {
    coords[i].y = game->height;
    coords[i].x = i;
  }
}

void ts_Game_getTopBorderCoords(ts_Game *game, ts_Coord *coords, uint8_t length)
{
int i = 0;
  for(i = 0; i < game->width && i < length; i++)
  {
    coords[i].y = 0;
    coords[i].x = i;
  }
}
