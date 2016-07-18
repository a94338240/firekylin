/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>
#include <errno.h>

static inline __syscall1(int, getime, time_t*, time_loc);

time_t time(time_t *tloc)
{
	return getime(tloc);
}
