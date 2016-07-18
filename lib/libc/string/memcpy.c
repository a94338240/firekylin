/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

void * memcpy(void *dst, const void *src, size_t n)
{
	char *d = (char*) dst;
	char *s = (char*) src;

	while (n--)
		*d++ = *s++;

	return dst;
}
