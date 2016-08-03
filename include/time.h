/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _TIME_H
#define _TIME_H

#include <sys/types.h>
#include <sys/param.h>

struct tm {
	int tm_sec; 	/* Seconds [0,60]. 		*/
	int tm_min; 	/* Minutes [0,59]. 		*/
	int tm_hour; 	/* Hour [0,23].    		*/
	int tm_mday; 	/* Day of month [1,31]. 	*/
	int tm_mon; 	/* Month of year [0,11].	*/
	int tm_year; 	/* Years since 1900(POSIX)	*/
	int tm_wday; 	/* Day of week [0,6] (Sunday=0).*/
	int tm_yday; 	/* Day of year [0,365].		*/
	int tm_isdst; 	/* Daylight Savings flag.	*/
};

struct timeval {
	time_t tv_sec; 	/* Seconds	*/
	long   tv_usec; /* Microseconds	*/
};

struct timespec {
	time_t tv_sec; 	/* Seconds	*/
	long   tv_nsec; /* Nanoseconds	*/
};

struct timezone {
	int    tz_minuteswest;
	int    tz_dsttime;
};

#define CLOCKS_PER_SEC 	HZ
#define CLK_TCK 	HZ

#define MIN    		(60L)
#define HOUR   		(60*MIN)
#define DAY    		(24*HOUR)
#define YEAR   		(365*DAY)
#define LEAPYEAR 	(366*DAY)

#define isleap(y)	(((y)%4==0&&(y)%100!=0)||(y)%400==0)

extern time_t     time(time_t *tloc);
extern time_t     mktime(struct tm *tmptr);
extern char *     asctime(struct tm *tmptr);
extern char *     ctime(time_t *tp);
extern struct tm* gmtime(time_t *tp);
extern struct tm* localtime(time_t *tp);
extern clock_t    clock(void);
extern double     difftime(time_t time1, time_t time0);
extern size_t     strftime(char *buf, size_t size, const char *fmt, struct tm *tmptr);

extern int gettimeofday(struct timeval *tv, struct timezone *tz);
extern int settimeofday(struct timeval *tv, struct timezone *tz);

#endif
