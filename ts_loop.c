#include "ts_loop.h"
#include <stdlib.h>
#include <sys/time.h>

ts_GameLoop ts_GameLoop_new(struct timeval rate)
{
  ts_GameLoop loop;

  gettimeofday(&loop.startTime, NULL);
  loop.rate = rate;

  return loop;
}

void ts_GameLoop_sleep(struct timeval tickStart)
{
}
