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
#include <sys/unistd.h>
#include <sys/stat.h>
#include <errno.h>

__syscall3(int, mknod, char *,filename, mode_t, mode, dev_t, dev);

