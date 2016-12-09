#include "ts_loop.h"
#include <stdlib.h>
#include <sys/time.h>
#include "util.h"

ts_GameLoop ts_GameLoop_new(struct timeval rate, struct timeval moveDelay)
{
  ts_GameLoop loop;

  gettimeofday(&loop.startTime, NULL);
  loop.rate = rate;
  loop.moveDelay = moveDelay;

  timeval_add(
      &loop.startTime,
      &loop.moveDelay,
      &loop.nextMove
      );

  return loop;
}

void ts_GameLoop_draw(ts_GameLoop *loop, ts_GameLoop_framefn fn)
{
  struct timeval tickStart, tickEnd, delay, toSleep;

  gettimeofday(&tickStart, NULL);
  fn();
  gettimeofday(&tickEnd, NULL);

  timeval_subtract(&tickEnd, &tickStart, &delay);

  if(!timeval_subtract(&loop->rate, &delay, &toSleep))
    nanosleep2(&toSleep);
}

void ts_GameLoop_move(ts_GameLoop *loop, ts_GameLoop_framefn fn)
{
struct timeval currentTime, result;
  gettimeofday(&currentTime, NULL);

  if(!timeval_subtract(&currentTime, &loop->nextMove, &result))
  {
    fn();
    timeval_add(&currentTime, &loop->moveDelay, &loop->nextMove);
  }
}
