/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fflush(FILE *stream)
{

	if (!stream){
		for (int i = 0; i < MAX_OPEN; i++)
			if (__iotab[i]._flag)
				fflush(&__iotab[i]);
	}

	if (stream->_flag & WRITING) {
		int size = stream->_ptr - stream->_buf;
		if (size && (write(stream->_fd, stream->_buf, size) != size)) {
			stream->_flag |= _IOERR;
		}
	}

	stream->_cnt = 0;
	stream->_ptr = stream->_buf;
	stream->_flag &= ~(READING | WRITING);

	return 0;
}
