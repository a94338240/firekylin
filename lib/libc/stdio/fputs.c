/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fputs(const char *s, FILE *stream)
{
	char *ts = (char*) s;
	int i = 0;
	int r;

	while (*ts) {
		r = fputc(*ts++, stream);
		i++;
		if (r == EOF)
			return 0;
	}

	return i;
}
