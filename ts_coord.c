#include "ts_coord.h"
#include "util.h"

ts_Coord ts_Coord_new(uint8_t y, uint8_t x)
{ return (ts_Coord){y, x}; }

bool ts_Coord_downCollision(ts_Coord *top, ts_Coord *bottom)
{
  return (
      top->x == bottom->x &&
        (top->y + 1) >= bottom->y
      );
}

bool ts_Coords_downCollision(ts_Coord *top, uint8_t topSize,
                             ts_Coord *bottom, uint8_t bottomSize)
{
  for(int i = 0; i < topSize; i++)
    for(int j = 0; j < bottomSize; j++)
      if(ts_Coord_downCollision(&top[i], &bottom[j]))
        return true;

  return false;
}

bool ts_Coord_leftCollision(ts_Coord *right, ts_Coord *left)
{
  return (
        right->y == left->y &&
        (left->x + 1) >= right->x
      );
}

bool ts_Coords_leftCollision(ts_Coord *right, uint8_t rightSize, ts_Coord *left, uint8_t leftSize)
{
  for(int i = 0; i < rightSize; i++)
    for(int j = 0; j < leftSize; j++)
      if(ts_Coord_leftCollision(&right[i], &left[j]))
        return true;

  return false;
}
