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

long long strtoll(const char *str, char **endptr, int base)
{
	long long ret = 0;
	char *p = (char *) str;
	int sig = 0;

	while (isspace(*p))
		p++;
	if (*p == '-') {
		sig = 1;
		p++;
	} else {
		if (*p == '+')
			p++;
	}
	while (isdigit(*p)) {
		ret = ret * 10 + *p - '0';
		p++;
	}
	if (endptr)
		*endptr = p;

	return sig ? ret : -ret;
}
