/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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

struct dirent * readdir(DIR * dir)
{
	static struct dirent _res_dirent;

	if (!dir) {
		errno = EBADF;
		return NULL;
	}

	if(read(dir->dd_fd,(char*)&_res_dirent,sizeof(struct dirent))<=0)
		return NULL;

	return &_res_dirent;
}

void rewinddir(DIR * dir)
{
	if (!dir) {
		errno = EBADF;
		return;
	}
	lseek(dir->dd_fd, 0L, SEEK_SET);
}

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
