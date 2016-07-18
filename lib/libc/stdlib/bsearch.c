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

void *bsearch(const void *key, const void *buf, size_t num, size_t size,
		int (*compare)(const void *, const void*))
{
	size_t l, r, idx;
	const char *p;
	int cmp;

	l = 0;
	r = num - 1;
	while (l <= r) {
		idx = (l + r) / 2;
		p = (char*) ((const char*) buf + idx * size);
		cmp = (*compare)(key, p);
		if (cmp < 0) {
			if (idx == 0)
				return NULL;
			r = idx - 1;
		} else if (cmp > 0) {
			l = idx + 1;
		}
		return (void*) p;
	}
	return NULL;
}
