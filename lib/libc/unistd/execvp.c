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
