#include "ts_game.h"
#include <stdlib.h>

static void spawnfailing(ts_Game *game)
{
  if(game->failing != NULL)
  {
    ts_Piece_destroy(game->failing);
    game->failing = NULL;
  }

  if(game->nextFailing == NULL) {
    game->nextFailing = ts_Piece_new(RANDOM_TETROMINO);
    game->failing = ts_Piece_new(RANDOM_TETROMINO);
  } else {
    ts_Piece_destroy(game->failing);
    game->failing = game->nextFailing;
    game->nextFailing = ts_Piece_new(RANDOM_TETROMINO);
  }

  game->failing->pos = (ts_Pos){0,game->board->width/2};
}

static void moveleft(ts_Game *game)
{
  ts_Board_remove_piece(game->board, game->failing);
  game->failing->pos.x--;

  if(!ts_Board_piecefits(game->board, game->failing))
    game->failing->pos.x++;

  ts_Board_put_piece(game->board, game->failing);
}

static void moveright(ts_Game *game)
{
  ts_Board_remove_piece(game->board, game->failing);
  game->failing->pos.x++;

  if(!ts_Board_piecefits(game->board, game->failing))
    game->failing->pos.x--;

  ts_Board_put_piece(game->board, game->failing);
}

static void rotate(ts_Game *game, int8_t direction)
{
  ts_Board_remove_piece(game->board, game->failing);

  ts_Piece_rotate(game->failing, direction);

  if(!ts_Board_piecefits(game->board, game->failing))
  {
    for(int i = 1; i < 3; i++)
    {
      ts_Piece_move(game->failing, 0, i);
      if(ts_Board_piecefits(game->board, game->failing))
        break;
      else
        ts_Piece_move(game->failing, 0, -i);

      ts_Piece_move(game->failing, 0, -i);
      if(ts_Board_piecefits(game->board, game->failing))
        break;
      else
        ts_Piece_move(game->failing, 0, i);
    }
  }

  ts_Board_put_piece(game->board, game->failing);
}

static void removeline(ts_Game *game, ts_PosNumber y_remove)
{
int y, x;
ts_Pos pos, ppos;

  for(y = y_remove; y >= 0; y--)
    for(x = 0; x < game->board->width; x++)
    {
      pos = (ts_Pos){y, x};
      ppos = (ts_Pos){y-1, x};

      if((y - 1) < 0)
        ts_Board_unset(game->board, &pos);
      else
        ts_Board_set(game->board, &pos, ts_Board_get(game->board, &ppos));
    }

  game->linesremoved++;
}

static void removelines(ts_Game *game)
{
ts_Pos pos;
int y, x;

  ts_Board_remove_piece(game->board, game->failing);

  for(y = 0; y < game->board->height; y++)
    for(x = 0; x < game->board->width; x++)
    {
      pos = (ts_Pos){y, x};

      if(ts_Board_get(game->board, &pos) == BOARD_EMPTY)
        break;
      else if(x == game->board->width - 1)
        removeline(game, y);
    }

  ts_Board_put_piece(game->board, game->failing);
}

ts_Game *ts_Game_new(ts_BoardDimension width, ts_BoardDimension height)
{
  ts_Game *game = calloc(1, sizeof(ts_Game));
  if(game != NULL) {
    game->finished = false;
    game->failing = NULL;
    game->nextFailing = NULL;
    game->board = ts_Board_new(width, height);
    spawnfailing(game);
  }
  return game;
}

void ts_Game_destroy(ts_Game *game)
{
  if(game->failing != NULL)
    ts_Piece_destroy(game->failing);

  ts_Board_destroy(game->board);
  free(game);
}

void ts_Game_fall(ts_Game *game)
{
  if(game->finished == true)
    return;

  ts_Board_remove_piece(game->board, game->failing);
  ts_Piece_move(game->failing, 1, 0);

  if(!ts_Board_piecefits(game->board, game->failing))
  {
    ts_Piece_move(game->failing, -1, 0);

    if(game->failing->pos.y == 0) {
      game->finished = true;
      return;
    } else {
      ts_Board_put_piece(game->board, game->failing);
      spawnfailing(game);
    }
  }

  ts_Board_put_piece(game->board, game->failing);
  removelines(game);
}

bool ts_Game_isfinished(ts_Game *game)
{ return game->finished; }

void ts_Game_move(ts_Game *game, ts_Movement movement)
{
  switch(movement) {
    case TS_LEFT:
      moveleft(game);
      break;
    case TS_RIGHT:
      moveright(game);
      break;
    case TS_ROTATE_CW:
      rotate(game, 1);
      break;
    case TS_ROTATE_CCW:
      rotate(game, -1);
      break;
    case TS_DOWN:
      break;
  };
}

int16_t ts_Game_getlinesremoved(ts_Game *game)
{ return game->linesremoved; }
