/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fputc(int ch, FILE *stream)
{
	if (!stream)
		return EOF;

	if (ferror(stream))
		return EOF;

	if (stream->_flag & READING)
		fflush(stream);

	if (stream->_cnt <= 0) {

		stream->_flag |=WRITING;

		if (!stream->_buf) {
			stream->_buf = malloc(BUFSIZ);
			if (!stream->_buf) {
				stream->_flag |= _IOERR;
				return EOF;
			}
			stream->_bufsize = BUFSIZ;
			stream->_ptr = stream->_buf;
		}

		int tmp = stream->_ptr - stream->_buf;
		if (tmp > 0) {
			if (write(stream->_fd, stream->_buf, tmp) != tmp) {
				stream->_flag |= _IOERR;
				return EOF;
			}
		}
		stream->_cnt = stream->_bufsize;
		stream->_ptr = stream->_buf;
	}

	stream->_cnt--;
	*stream->_ptr++ = ch;

	return ch;
}
