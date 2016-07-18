/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

size_t strspn(const char *s1, const char *s2)
{
	char *ts1, *ts2;

	for (ts1 = (char *) s1; *ts1; ts1++) {
		for (ts2 = (char*) s2; *ts2; ts2++) {
			if (*ts1 == *ts2)
				break;
		}
		if (*ts2 == '\0')
			break;

	}
	return (size_t) (ts1 - s1);
}
