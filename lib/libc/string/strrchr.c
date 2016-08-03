/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

char * strrchr(const char * str, int ch)
{
	char *s = (char *) str;
	while (*s)
		s++;

	while (s-- != str && *s != (char) ch)
		;

	return s <= str ? NULL : s;
}
