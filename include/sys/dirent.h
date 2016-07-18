/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

#define MAX_NAME_LEN	255
struct dirent{
	ino_t  d_ino;
	size_t d_reclen;
	char   d_name[MAX_NAME_LEN+1];
};

typedef struct {
	int    dd_fd;
} DIR;

DIR           *opendir(char *filename);
struct dirent *readdir(DIR *dir);
void           rewinddir(DIR *dir);
int            closedir(DIR *dir);

#endif
