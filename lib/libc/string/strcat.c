/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

char * strcat(char *s1, const char *s2)
{
	char *tmp = s1;
	char *tmp2 = (char*) s2;
	while (*tmp)
		tmp++;
	while (*tmp2)
		*tmp++ = *tmp2++;
	return s1;
}
