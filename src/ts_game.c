#include "ts_game.h"
#include <stdlib.h>

static void spawnfalling(ts_Game *game)
{
  if(game->falling != NULL)
  {
    ts_Piece_destroy(game->falling);
    game->falling = NULL;
  }

  if(game->nextFalling == NULL) {
    game->nextFalling = ts_Piece_new(RANDOM_TETROMINO);
    game->falling = ts_Piece_new(RANDOM_TETROMINO);
  } else {
    ts_Piece_destroy(game->falling);
    game->falling = game->nextFalling;
    game->nextFalling = ts_Piece_new(RANDOM_TETROMINO);
  }

  game->falling->pos = (ts_Pos){0,game->board->width/2};
}

static void moveleft(ts_Game *game)
{
  ts_Board_remove_piece(game->board, game->falling);
  game->falling->pos.x--;

  if(!ts_Board_piecefits(game->board, game->falling))
    game->falling->pos.x++;

  ts_Board_put_piece(game->board, game->falling);
}

static void moveright(ts_Game *game)
{
  ts_Board_remove_piece(game->board, game->falling);
  game->falling->pos.x++;

  if(!ts_Board_piecefits(game->board, game->falling))
    game->falling->pos.x--;

  ts_Board_put_piece(game->board, game->falling);
}

static void rotate(ts_Game *game, int8_t direction)
{
  ts_Board_remove_piece(game->board, game->falling);

  ts_Piece_rotate(game->falling, direction);

  if(!ts_Board_piecefits(game->board, game->falling))
  {
    for(int i = 1; i < 3; i++)
    {
      ts_Piece_move(game->falling, 0, i);
      if(ts_Board_piecefits(game->board, game->falling))
        break;
      else
        ts_Piece_move(game->falling, 0, -i);

      ts_Piece_move(game->falling, 0, -i);
      if(ts_Board_piecefits(game->board, game->falling))
        break;
      else
        ts_Piece_move(game->falling, 0, i);
    }
  }

  ts_Board_put_piece(game->board, game->falling);
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

  ts_Board_remove_piece(game->board, game->falling);

  for(y = 0; y < game->board->height; y++)
    for(x = 0; x < game->board->width; x++)
    {
      pos = (ts_Pos){y, x};

      if(ts_Board_get(game->board, &pos) == BOARD_EMPTY)
        break;
      else if(x == game->board->width - 1)
        removeline(game, y);
    }

  ts_Board_put_piece(game->board, game->falling);
}

ts_Game *ts_Game_new(ts_BoardDimension width, ts_BoardDimension height)
{
  ts_Game *game = calloc(1, sizeof(ts_Game));
  if(game != NULL) {
    game->finished = false;
    game->falling = NULL;
    game->nextFalling = NULL;
    game->board = ts_Board_new(width, height);
    spawnfalling(game);
  }
  return game;
}

void ts_Game_destroy(ts_Game *game)
{
  if(game->falling != NULL)
    ts_Piece_destroy(game->falling);

  ts_Board_destroy(game->board);
  free(game);
}

void ts_Game_fall(ts_Game *game)
{
  if(game->finished == true)
    return;

  ts_Board_remove_piece(game->board, game->falling);
  ts_Piece_move(game->falling, 1, 0);

  if(!ts_Board_piecefits(game->board, game->falling))
  {
    ts_Piece_move(game->falling, -1, 0);

    if(game->falling->pos.y == 0) {
      game->finished = true;
      return;
    } else {
      ts_Board_put_piece(game->board, game->falling);
      spawnfalling(game);
    }
  }

  ts_Board_put_piece(game->board, game->falling);
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

void ts_Game_levelAndScore(ts_Game *game, int *level, int *score)
{
int _level = 1, _score = 0;

  for(int i = 0; i <= game->linesremoved; i++)
  {
    if(i == 0)
      continue;

    _score += _level * LEVEL_MULTIPLIER;

    if(i % LINES_PER_LEVEL == 0)
    {
      _level++;
    }
  }

  *level = _level;
  *score = _score;
}
