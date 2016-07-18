/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <time.h>
#include <sys/times.h>

clock_t clock(void)
{
	struct tms tmsptr;

	times(&tmsptr);
	return tmsptr.tms_utime + tmsptr.tms_stime;
}
