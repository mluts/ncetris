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

ts_GameLoop ts_GameLoop_new(struct timeval rate);
ts_GameLoop ts_gameLoop_sleep(struct timeval tickStart);

#endif
