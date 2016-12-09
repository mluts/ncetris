#include "ts_coord.h"
#include "util.h"

ts_Coord ts_Coord_new(uint8_t y, uint8_t x)
{ return (ts_Coord){y, x}; }
