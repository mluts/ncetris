#include "ts_loop.h"
#include <stdlib.h>
#include <sys/time.h>
#include <util.h>

ts_GameLoop *ts_GameLoop_new(struct timeval frameRate)
{
  ts_GameLoop *loop;
  loop = calloc(1, sizeof(ts_GameLoop));

  if(loop != NULL) {
    loop->frameRate = frameRate;
  }

  return loop;
}

void ts_GameLoop_destroy(ts_GameLoop *loop)
{ free(loop); }

void ts_GameLoop_startFrame(ts_GameLoop *loop)
{
  loop->ticks++;
  gettimeofday(&loop->startFrameTime, NULL);
}

void ts_GameLoop_stopFrame(ts_GameLoop *loop)
{
  gettimeofday(&loop->stopFrameTime, NULL);

  timeval_subtract(
      &loop->stopFrameTime,
      &loop->startFrameTime,
      &loop->frameDelay
      );

  if(!timeval_subtract(
        &loop->frameRate,
        &loop->frameDelay,
        &loop->toSleep))
    nanosleep2(&loop->toSleep);
}

int32_t ts_GameLoop_getticks(ts_GameLoop *loop)
{ return loop->ticks; }
