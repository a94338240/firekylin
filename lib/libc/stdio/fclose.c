/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "stdio_loc.h"

int fclose(FILE *stream)
{

	if (!stream)
		return EOF;

	fflush(stream);

	if (stream->_buf){
		free(stream->_buf);
		stream->_buf=NULL;
	}

	stream->_flag=0;
	return close(stream->_fd);
}
