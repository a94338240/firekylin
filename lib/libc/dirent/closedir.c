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
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

int closedir(DIR * dir)
{
	int fd;

	if (!dir) {
		errno = EBADF;
		return -1;
	}

	fd = dir->dd_fd;
	free(dir);

	return close(fd);
}
