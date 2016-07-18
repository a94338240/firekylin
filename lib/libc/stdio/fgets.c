/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

char * fgets(char * buf, size_t n, FILE *stream)
{
	int c;
	char *p = buf;

	while (n-- && (c = fgetc(stream)) != EOF ) {
		*p++ = c;
		if (c == '\n')
			break;
	}

	if (feof(stream))
		return NULL;

	if(n)
		*p=0;
	return (p == buf) ? NULL : buf;
}
