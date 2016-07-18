/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

/* clock interrupt one seconds */
#define HZ		100

/* Max file open one task */
#define NR_OPEN		32

/* Max task exsit */
#define NR_TASK		16

/* Max inode cache in memory */
#define NR_INODE	32

/* Max supper block in system */
#define NR_SUPER	4

/* Mac buffer cache in system */
#define NR_BUFFER	64

/* buffer cache size */
#define BUF_SIZE	1024

#endif
