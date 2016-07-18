/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int sprintf(char * buf, const char *fmt,...)
{
	va_list ap;
	int i;

	i=vsprintf(buf, fmt, va_start(ap,fmt));

	return i;
}
