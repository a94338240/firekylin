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
#include <sys/unistd.h>

int printf(char *fmt, ...)
{
	char buf[2048];
	va_list ap;
	int i;

	i = vsnprintf(buf, 2048, fmt, va_start(ap, fmt));
	write(STDOUT_FILENO, buf, i);
	return i;
}
