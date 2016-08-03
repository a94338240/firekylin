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
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static struct dirent _res_dirent;

struct dirent * readdir(DIR * dir)
{
	if (!dir) {
		errno = EBADF;
		return NULL;
	}

	if(read(dir->dd_fd,(char*)&_res_dirent,sizeof(struct dirent))<=0)
		return NULL;

	return &_res_dirent;
}
