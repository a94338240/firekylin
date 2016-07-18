/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fseek(FILE *stream, off_t offset, int where)
{
	if(!stream)
		return EOF;

	fflush(stream);

	return lseek(stream->_fd, offset, where);
}
