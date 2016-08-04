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
static struct tm st;

struct tm *gmtime(time_t *t)
{
	struct tm *stm=&st;
	time_t time = *t;

	int year, mday, i;

	if (time < 0) /* negative times are bad */
		return 0;
	stm->tm_wday = ((time / DAY) + 4) % 7;

	year = 1970;
	for (;;) {
		if (time < YEAR)
			break;
		if ((year % 4) == 0) {
			if (time < LEAPYEAR)
				break;
			else
				time -= LEAPYEAR;
		} else
			time -= YEAR;
		year++;
	}
	stm->tm_year = year;
	mday = stm->tm_yday = time / DAY;
	days_per_mth[1] = (year % 4) ? 28 : 29;
	for (i = 0; mday >= days_per_mth[i]; i++)
		mday -= days_per_mth[i];
	stm->tm_mon = i;
	stm->tm_mday = mday + 1;
	time = time % DAY;
	stm->tm_hour = time / HOUR;
	time = time % HOUR;
	stm->tm_min = time / MIN;
	stm->tm_sec = time % MIN;
	stm->tm_isdst = 0;
	return stm;
}
