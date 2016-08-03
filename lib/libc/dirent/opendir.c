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

DIR * opendir(char * dirname)
{
	struct stat statbuf;
	DIR *dir;
	int  fd;

	if ((fd = open(dirname, O_READ)) < 0)
		return NULL;

	if (fstat(fd, &statbuf) < 0 ||
	    !S_ISDIR(statbuf.st_mode) ||
	    !(dir =malloc(sizeof(DIR)))) {
		close(fd);
		return NULL;
	}

	dir->dd_fd = fd;

	return dir;
}
