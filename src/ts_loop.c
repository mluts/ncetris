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
  loop->frames++;
  gettimeofday(&loop->startFrameTime, NULL);
}

void ts_GameLoop_stopFrame(ts_GameLoop *loop)
{
struct timeval toSleep, stopFrameTime, frameDelay;

  gettimeofday(&stopFrameTime, NULL);

  timeval_subtract(
      &stopFrameTime,
      &loop->startFrameTime,
      &frameDelay
      );

  if(!timeval_subtract(
        &loop->frameRate,
        &frameDelay,
        &toSleep))
    nanosleep2(&toSleep);
}

int32_t ts_GameLoop_getframes(ts_GameLoop *loop)
{ return loop->frames; }
