#ifndef _UTIL_H
#define _UTIL_H
#include <sys/time.h>
#include <stdio.h>

#define MILLION 1000000

int timeval_subtract(
    const struct timeval *x,
    const struct timeval *y,
    struct timeval *result)
{
  int negative = 0;

  if(x->tv_usec < y->tv_usec) {
    result->tv_sec = x->tv_sec - y->tv_sec - 1;
    result->tv_usec = MILLION - (y->tv_usec - x->tv_usec);
  } else {
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;
  }

  negative = result->tv_sec < 0;

  if(result->tv_sec < 0 && result->tv_usec > 0) {
    result->tv_sec++;
    result->tv_usec = MILLION - result->tv_usec;
  }

  if(result->tv_sec < 0) {
    result->tv_sec *= -1;
  }

  return negative;
}

#endif
