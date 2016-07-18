/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _LOCALE_H
#define _LOCALE_H

#define LC_ALL	 	1	
#define LC_COLLATE	1
#define LC_CTYPE	1
#define LC_MONETARY	1
#define LC_TIME		0
#define LC_NUMERIC	0	

/* unimpliment */
struct lconv {
	char decimal_point[10];
};

static inline char * setlocale(int category, const char *locale)
{
	return (void*) 0;
}

static inline struct lconv * localeconv()
{
	return (void*) 0;
}

#endif
