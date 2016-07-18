/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>
#include <ctype.h>

int strnicmp(const char *s1, const char *s2, size_t n)
{
	char *ts1=(char *)s1;
	char *ts2=(char *)s2;

	while (n--) {
		if (*ts1 && (toupper(*ts1) == toupper(*ts2))) {
			ts1++;
			ts2++;
		} else {
			return (*ts1 - *ts2);
		}
	}
	return 0;
}
