/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <math.h>

double frexp(double x, int *exptr)
{
	int i = 0;
	while (x > 1) {
		x = x / 2.0;
		i++;
	}
	*exptr = i;
	return x;
}
