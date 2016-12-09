#ifndef _TS_COORD_H
#define _TS_COORD_H
#include <stdint.h>
#include <stdbool.h>

typedef struct { uint8_t y, x; } ts_Coord;
ts_Coord ts_Coord_new(uint8_t y, uint8_t x);
#endif
