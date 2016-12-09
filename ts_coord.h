#ifndef _TS_COORD_H
#define _TS_COORD_H
#include <stdint.h>
#include <stdbool.h>

typedef struct { uint8_t y, x; } ts_Coord;
ts_Coord ts_Coord_new(uint8_t y, uint8_t x);
bool ts_Coord_downCollision(ts_Coord *top, ts_Coord *bottom);
bool ts_Coords_downCollision(ts_Coord *top, uint8_t topSize, ts_Coord *bottom, uint8_t bottomSize);
bool ts_Coord_leftCollision(ts_Coord *right, ts_Coord *left);
bool ts_Coords_leftCollision(ts_Coord *right, uint8_t rightSize, ts_Coord *left, uint8_t leftSize);
#endif
