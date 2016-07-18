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
#include <errno.h>

void perror(const char *s)
{
	fprintf(stderr, "%s:%s", s, strerror(errno));
	fflush(stderr);
}
