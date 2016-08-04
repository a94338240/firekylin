/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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
