/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

char *getcwd(char *buf, int buflen)
{
	char buf1[PATH_MAX], buf2[PATH_MAX];
	struct stat st;
	dev_t c_dev;
	ino_t c_ino;
	struct dirent *de;
	DIR *dp;
	int fd;
	int len;
	char *res = NULL;

	fd = open(".", O_RDWR);
	if (fd < 0)
		return NULL;

	memset(buf1, 0, PATH_MAX);
	memset(buf2, 0, PATH_MAX);

	while (1) {
		if (stat(".", &st) < 0)
			goto err;
		c_ino = st.st_ino;
		c_dev = st.st_dev;

		dp = opendir("..");
		if (!dp)
			goto err;
		chdir("..");
		while ((de = readdir(dp))) {
			if (!strcmp(de->d_name, "."))
				continue;

			if (stat(de->d_name, &st) < 0)
				goto err;

			if ((st.st_ino == c_ino) && (st.st_dev == c_dev)) {
				if (!strcmp(de->d_name, ".."))
					goto out;
				sprintf(buf2, "%s/%s", de->d_name, buf1);
				strncpy(buf1, buf2, PATH_MAX);
				closedir(dp);
				break;
			}
		}
	}
out:
	len = strnlen(buf1, PATH_MAX);
	if (buflen < len + 1)
		goto err;

	int i = sprintf(buf, "/%s", buf1);
	if (i > 1)
		buf[i - 1] = 0;
	buf[i] = 0;
	res = buf;
err:
	fchdir(fd);
	close(fd);
	return res;
}
