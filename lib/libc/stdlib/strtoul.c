/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdlib.h>
#include <ctype.h>

unsigned long strtoul(const char *str, char **endptr, int base)
{
	unsigned long ret = 0;
	char *p = (char *) str;

	while (isspace(*p))
		p++;
	while (isdigit(*p)) {
		ret = ret * 10 + *p - '0';
		p++;
	}
	if (endptr)
		*endptr = p;

	return ret;
}
