/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

FILE *fdopen(int fd, const char *mode)
{
	FILE *f;

	if (fd < 0)
		return NULL;

	for (int i = 0; i < MAX_OPEN; i++) {
		if (__iotab[i]._flag)
			continue;
		f = &__iotab[i];
		f->_fd=fd;
		f->_flag=_IOFBF;
		f->_cnt=0;
		f->_bufsize=0;
		f->_buf=NULL;
		f->_ptr=NULL;
		return f;
	}
	return NULL;
}
