/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _ASSERT_H
#define _ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef	NDEBUG
#define assert(expr)
#else

#define assert(expr) 							\
    if(!(expr)){							\
	fprintf(stderr, "Assertion failed: %s , file %s, line %d", 	\
			#expr, __FILE__, __LINE__ );			\
	abort();							\
    }

#endif

#endif
