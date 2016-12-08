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

void ts_Game_move(ts_Game *game)
{
  if(game->piece == NULL) {
  }
}
