/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdlib.h>
#include <string.h>

void * realloc(void *ptr, size_t size)
{
	void *tmp;

	tmp = malloc(size);

	if (!tmp)
		return NULL;

	if (ptr) {
		memcpy((char*) tmp, (char*) ptr, size);
		free(ptr);
	}
	return tmp;
}
