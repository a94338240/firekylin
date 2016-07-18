/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdint.h>

uint64_t __umoddi3(uint64_t a, uint64_t b)
{
	if (b == 0)
		return (uint64_t) -1;

	while (a > b)
		a = a - b;

	return a;
}
