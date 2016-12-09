#ifndef _TS_LOOP_H
#define _TS_LOOP_H
#include <stdbool.h>
#include <sys/time.h>

typedef struct {
  struct timeval rate;
  struct timeval startTime;
  struct timeval moveDelay;
  struct timeval nextMove;
} ts_GameLoop;

typedef void (*ts_GameLoop_framefn)(void);

ts_GameLoop ts_GameLoop_new(struct timeval rate, struct timeval moveDelay);
void ts_GameLoop_draw(ts_GameLoop *, ts_GameLoop_framefn);
void ts_GameLoop_move(ts_GameLoop *, ts_GameLoop_framefn);

#endif
