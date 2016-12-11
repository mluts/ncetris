#ifndef _TS_LOOP_H
#define _TS_LOOP_H
#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct {
  struct timeval frameRate,
                 startFrameTime;
  int32_t frames;
} ts_GameLoop;

ts_GameLoop *ts_GameLoop_new(struct timeval frameRate);
void ts_GameLoop_destroy(ts_GameLoop *);
void ts_GameLoop_startFrame(ts_GameLoop *);
void ts_GameLoop_stopFrame(ts_GameLoop *);
int32_t ts_GameLoop_getframes(ts_GameLoop *);

#endif
