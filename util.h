#ifndef _UTIL_H
#define _UTIL_H

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#define MILLION 1000000
#define INFO(msg) fprintf(stdout, "INFO: %s:%d:%s %s\n", __FILE__,__LINE__,__func__,msg);

int timeval_subtract(
    const struct timeval *x,
    const struct timeval *y,
    struct timeval *result);

void timeval_add(
    const struct timeval *x,
    const struct timeval *y,
    struct timeval *result);

void nanosleep2(const struct timeval *time);

#endif
