/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int execlp(const char * file, char * arg0, ...)
{
	return execvep(file, &arg0, environ);
}
