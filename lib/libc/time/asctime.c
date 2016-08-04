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
