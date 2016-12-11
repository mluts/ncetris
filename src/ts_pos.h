#ifndef _TS_POS_H
#define _TS_POS_H
#include <stdint.h>
typedef int16_t ts_PosNumber;
typedef struct {
  ts_PosNumber y, x;
} ts_Pos;
#endif
