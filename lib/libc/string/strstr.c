/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

char * strstr(const char *s1, const char *s2)
{
	if (*s1 == 0) {
		if (*s2) {
			return NULL;
		}
		return (char *) s1;
	}
	while (*s1) {
		size_t i=0;
		while (1) {
			if (s2[i] == 0) {
				return (char *) s1;
			}
			if (s2[i] != s1[i]) {
				break;
			}
			i++;
		}
		s1++;
	}
	return NULL;
}
