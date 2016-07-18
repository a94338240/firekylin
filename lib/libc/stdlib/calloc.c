/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void * calloc(size_t nelem, size_t elsize)
{
	void *tmp;
	int size = nelem * elsize;

	tmp = malloc(size);
	if (!tmp)
		return NULL;
	memset((char*) tmp, 0, size);
	return tmp;
}
