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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char * attr(struct stat *buf)
{
	static char attr_buf[11];

	memset(attr_buf, '-', 10);

	if (S_ISLNK(buf->st_mode))
		attr_buf[0] = 'l';
	else if (S_ISDIR(buf->st_mode))
		attr_buf[0] = 'd';
	else if (S_ISCHR(buf->st_mode))
		attr_buf[0] = 'c';
	else if (S_ISBLK(buf->st_mode))
		attr_buf[0] = 'b';
	else if (S_ISFIFO(buf->st_mode))
		attr_buf[0] = 'p';
	else if (S_ISSOCK(buf->st_mode))
		attr_buf[0] = 's';

	if (buf->st_mode & S_IRUSR)
		attr_buf[1] = 'r';
	if (buf->st_mode & S_IWUSR)
		attr_buf[2] = 'w';
	if (buf->st_mode & S_IXUSR)
		attr_buf[3] = 'x';
	if (buf->st_mode & S_IRGRP)
		attr_buf[4] = 'r';
	if (buf->st_mode & S_IWGRP)
		attr_buf[5] = 'w';
	if (buf->st_mode & S_IXGRP)
		attr_buf[6] = 'x';
	if (buf->st_mode & S_IROTH)
		attr_buf[7] = 'r';
	if (buf->st_mode & S_IWOTH)
		attr_buf[8] = 'w';
	if (buf->st_mode & S_IXOTH)
		attr_buf[9] = 'x';
	attr_buf[10] = 0;
	return attr_buf;
}

static int opt_a, opt_l;

void out(char *name, struct stat *buf)
{
	if (opt_l)
		printf("%s  %3d  %5d %s %-s\n", attr(buf), buf->st_nlink,
				buf->st_size, ctime(&(buf->st_atime)), name);
	else
		printf("%-10s", name);
}

int do_ls(char *name)
{
	struct stat buf;
	DIR *dp;
	struct dirent *de;
	char path[256];
	int i;

	if (stat(name, &buf) < 0) {
		printf("stat error:%s\n", name);
		return 0;
	}

	if (!S_ISDIR(buf.st_mode)) {
		out(name, &buf);
		return 0;
	}

	dp = opendir(name);
	if (!dp) {
		printf("diropen error:%s", name);
		return 0;
	}

	while ((de = readdir(dp))) {
		if (de->d_name[0] == '.' && (!opt_a))
			continue;
		if (name[strlen(name) - 1] == '/')
			i = sprintf(path, "%s%s", name, de->d_name);
		else
			i = sprintf(path, "%s/%s", name, de->d_name);
		path[i] = 0;
		if ((stat(path, &buf) < 0)) {
			printf("stat fail %s", path);
			continue;
		}
		out(de->d_name, &buf);
	}
	closedir(dp);
	return 0;
}

int main(int argc, char **argv)
{
	int count = 0;
	opt_a = opt_l = 0;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'a' && argv[i][2] == 0) {
				opt_a = 1;
				continue;
			}
			if (argv[i][1] == 'l' && argv[i][2] == 0) {
				opt_l = 1;
				continue;
			}
			continue;
		}
		do_ls(argv[i]);
		count++;
	}
	if (!count)
		do_ls(".");
	if (!opt_l)
		printf("\n");
	return 0;
}
