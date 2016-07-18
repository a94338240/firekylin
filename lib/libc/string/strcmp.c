/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

int strcmp(const char *s1, const char *s2)
{
	char *t_s1 = (char*) s1;
	char *t_s2 = (char *) s2;
	while (*t_s1 && *t_s2 && *t_s1 == *t_s2) {
		t_s1++;
		t_s2++;
	}

	return (int) (*t_s1 - *t_s2);
}
