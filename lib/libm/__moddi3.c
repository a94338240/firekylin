/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdint.h>

int64_t __moddi3(int64_t a, int64_t b)
{
	int sign1 = 0, sign2 = 0;

	if (a < 0) {
		sign1 = 1;
		a = -a;
	}
	if (b < 0) {
		sign2 = 1;
		b = -b;
	}
	if (b == 0)
		return (int64_t) -1;

	while (a > b)
		a = a - b;

	return (sign1 ^ sign2) ? -a : a;
}
