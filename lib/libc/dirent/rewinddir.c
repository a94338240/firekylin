/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/dirent.h>
#include <errno.h>

void rewinddir(DIR * dir)
{
	if (!dir) {
		errno = EBADF;
		return;
	}
	lseek(dir->dd_fd, 0L, SEEK_SET);
}
