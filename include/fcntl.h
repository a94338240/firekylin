/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _FCNTL_H
#define _FCNTL_H

//#pragma  message("<fcntl.h> Deprecated, use <sys/fcntl.h> instead")
//#pragma  message("O_RDONLY Deprecated, use O_READ instead")
//#pragma  message("O_WRONLY Deprecated, use O_WRITE instead")

#include <sys/fcntl.h>

#define O_RDONLY	O_READ
#define O_WRONLY	O_WRITE

#endif
