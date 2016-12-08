#ifndef _UTIL_H
#define _UTIL_H

#include <time.h>
#include <sys/time.h>

#define MILLION 1000000

int timeval_subtract(
    const struct timeval *x,
    const struct timeval *y,
    struct timeval *result);

void nanosleep2(const struct timeval *time);

#endif
