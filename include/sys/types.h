/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#ifndef NULL
#define NULL 		((void*)0)
#endif

typedef unsigned long 	size_t;
typedef signed   long 	ssize_t;

typedef unsigned long 	time_t;
typedef unsigned long 	clock_t;

typedef signed int 	uid_t;
typedef signed int 	gid_t;
typedef signed int 	pid_t;

typedef unsigned int 	dev_t;
typedef unsigned int 	ino_t;
typedef unsigned int 	mode_t;
typedef unsigned int 	nlink_t;

typedef unsigned long 	off_t;

#endif
