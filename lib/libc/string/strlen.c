/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

size_t strlen(const char *s)
{
	char *p = (char*) s;
	while (*p)
		p++;
	return (size_t) (p - s);
}
