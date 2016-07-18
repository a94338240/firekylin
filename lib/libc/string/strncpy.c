/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

char *strncpy(char *dst, const char *src, size_t n)
{
	char *t = dst;
	char *t2=(char *)src;

	while (n-- && *t2)
		*t++ = *t2++;
	if(n)
		*t=0;
	return dst;
}
