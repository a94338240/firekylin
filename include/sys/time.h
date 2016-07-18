/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <sys/types.h>
#include <sys/param.h>

#define CLOCKS_PER_SEC 	HZ
#define CLK_TCK 	HZ

#define isleap(y)	(((y)%4==0&&(y)%100!=0)||(y)%400==0)

struct timezone {
	int    tz_minuteswest;
	int    tz_dsttime;
};

struct timeval {
	time_t tv_sec; 	/* Seconds	*/
	long   tv_usec; /* Microseconds	*/
};

struct timespec {
	time_t tv_sec; 	/* Seconds	*/
	long   tv_nsec; /* Nanoseconds	*/
};

extern int gettimeofday(struct timeval *tv, struct timezone *tz);
extern int settimeofday(struct timeval *tv, struct timezone *tz);

#endif
