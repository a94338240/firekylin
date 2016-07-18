/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

void * memchr(const void * buf, int chr, size_t n)
{
	char *s = (char *) buf;

	while (--n && *s != chr) {
		s++;
	}

	return n ? s : NULL;
}
