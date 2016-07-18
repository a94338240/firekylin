/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

char *strncat(char *s1, const char *s2 ,size_t n)
{
	char *tmp = s1;
	char *ts2=(char *)s2;

	while (*tmp)
		tmp++;

	while (n-- && *ts2)
		*tmp++ = *ts2++;

	return s1;
}
