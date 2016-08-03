/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <time.h>

struct tm *localtime(time_t * t)
{
	//time_t offset = *t; /* seconds between local time and GMT */

	//if (timezone == -1) tzset();
	// offset = *t - timezone;

	//if (stm == (struct tm *)NULL) return stm; /* check for illegal time */
	//stm->tm_isdst = (dst == -1) ? -1 : 0;
	return gmtime(t);;
}
