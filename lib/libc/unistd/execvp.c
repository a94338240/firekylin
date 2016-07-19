/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int execvp(const char *file, char **argv)
{
	char *path, *tmp;
	struct stat st;
	char tmp_path[PATH_MAX];
	int len;

	if (*file == '/' || !(path = getenv("PATH")))
		return execve(file, argv, environ);

	while (*path) {
		tmp = tmp_path;
		len = 0;
		while (len < PATH_MAX && *path && *path != ':') {
			*(tmp++) = *(path++);
			len++;
		}
		if (*path == ':')
			path++;
		if (!len || tmp[-1] != '/') {
			*(tmp++) = '/';
			len++;
		}
		if (len >= PATH_MAX)
			continue;
		strncpy(tmp, file, PATH_MAX - len);

		if (stat(tmp_path, &st))
			continue;
		else if (!(st.st_mode & S_IFREG))
			continue;
		return execve(tmp_path, argv, environ);
	}
	errno = ENOENT;
	return -1;
}
