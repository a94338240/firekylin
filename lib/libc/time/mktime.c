/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <time.h>

static int days_per_mth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

time_t mktime(struct tm * t)
{
	time_t s;
	int y;

	y = t->tm_year - 70;
	if (y < 0) /* year before 1970 */
		return (time_t) -1;
	s = (YEAR * y) + (((y + 1) / 4) * DAY);
	/* extra days for leap years */
	if ((y + 2) % 4)
		days_per_mth[1] = 28;
	else
		days_per_mth[1] = 29;

	for (y = 0; y < t->tm_mon; y++)
		s += DAY * days_per_mth[y];

	s += (t->tm_mday - 1) * DAY;
	s += t->tm_hour * HOUR;
	s += t->tm_min * MIN;
	s += t->tm_sec;
	return s;
}
