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

long double strtold(const char *ptr, char **endptr)
{
	long double ret = 0;
	double sal = 0.1;
	char *p = (char *) ptr;

	while (isspace(*p))
		p++;
	while (isdigit(*p)){
		ret = ret * 10 + *p - '0';
		p++;
	}
	if (*p == '.') {
		p++;
		while (isdigit(*p)) {
			ret += (*p - '0') * sal;
			sal = sal / 10;
			p++;
		}
	}
	if (endptr)
		*endptr = p;
	return ret;
}
