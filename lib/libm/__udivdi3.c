/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdint.h>

uint64_t __udivdi3(uint64_t a, uint64_t b)
{
	uint64_t ret = 0;

	if (b == 0)
		return (uint64_t) 0;
	while (a > b) {
		a = a - b;
		ret++;
	}
	return ret;
}
