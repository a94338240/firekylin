/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdlib.h>

static int __seed;

int rand(void)
{
	if(__seed==0)
		__seed++;
	__seed=__seed*123044543+12345;
	return __seed-1;
}

void srand(unsigned int seed)
{
	__seed=(int)seed;
}
