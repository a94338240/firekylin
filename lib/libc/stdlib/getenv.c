/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdlib.h>
#include <string.h>

char * getenv(const char * name)
{
	int len = strlen(name);
	char ** env = environ;
	char * tmp;

	while (*env) {
		tmp = *env++;
		if (strncmp(name, tmp, len))
			continue;
		if (tmp[len] == '=')
			return tmp + len + 1;
	}
	return NULL;
}
