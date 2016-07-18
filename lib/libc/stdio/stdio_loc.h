/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STDIO_LOC_H
#define _STDIO_LOC_H

#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_OPEN	NR_OPEN

extern FILE __iotab[];

#define READING		0x0100
#define WRITING		0x0200

#endif
