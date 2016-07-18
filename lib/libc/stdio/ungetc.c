/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int ungetc(int c, FILE *stream)
{
	if (!stream)
		return EOF;
	if (!(stream->_flag & READING))
		return EOF;
	if (!stream->_buf)
		return EOF;
	if (stream->_ptr <= stream->_buf)
		return EOF;

	stream->_cnt++;
	*--stream->_ptr = c;

	return c;
}
