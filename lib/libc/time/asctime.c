/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <time.h>
#include <stdio.h>
#include <string.h>

static const char *day[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

static const char *month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
		"Aug", "Sep", "Oct", "Nov", "Dec" };

char * asctime(struct tm * time)
{
	static char buf[40];
	int i=0;

	if (time == NULL)
		strcpy(buf, "??? ??? ?? ??:??:?? ????\n");
	else{
		i=sprintf(buf, "%.3s %.3s %2d %02d:%02d:%02d %04d",
				day[time->tm_wday], month[time->tm_mon],
				time->tm_mday, time->tm_hour, time->tm_min,
				time->tm_sec, 1900 + time->tm_year);
		buf[i]=0;
	}
	return (buf);
}
