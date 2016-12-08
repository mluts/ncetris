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
