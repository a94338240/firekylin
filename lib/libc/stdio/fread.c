/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

size_t fread(void * ptr, size_t size, size_t nobj, FILE *stream)
{
	int tmp_len, done, c;
	char *buf = (char*) ptr;

	tmp_len = size * nobj;
	if (!tmp_len)
		return 0;

	while (tmp_len--) {
		c = fgetc(stream);
		if (c == EOF)
			break;
		*buf++ = c;
		done++;
	}

	return done / size;
}
