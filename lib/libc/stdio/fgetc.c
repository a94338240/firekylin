/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fgetc(FILE *stream)
{
	if (!stream)
		return EOF;

	if (ferror(stream))
		return EOF;
	if (stream->_flag & WRITING)
		fflush(stream);

	if (stream->_cnt <= 0) {

		if (!stream->_buf) {
			stream->_buf = malloc(BUFSIZ);
			if (!stream->_buf) {
				stream->_flag |= _IOERR;
				return EOF;
			}
			stream->_bufsize = BUFSIZ;
		}

		stream->_flag |= READING;
		stream->_cnt = read(stream->_fd, stream->_buf,
				stream->_bufsize);

		if (stream->_cnt < 0) {
			stream->_flag |= _IOERR;
			return EOF;
		}
		if (stream->_cnt == 0) {
			stream->_flag |= _IOEOF;
			return EOF;
		}

		stream->_ptr = stream->_buf;
	}

	stream->_cnt--;

	return *stream->_ptr++;
}
