/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

char *strcpy(char *dst, const char *src)
{
	char *tmp = dst;
	char *t =(char *)src;
	while (*t)
		*tmp++ = *t++;
	*tmp = 0;
	return dst;
}
