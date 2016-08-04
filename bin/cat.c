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
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char buf[1024];

void do_cat(int fd)
{
	int size;
	while ((size = read(fd, buf, 1024)) > 0)
		write(STDOUT_FILENO, buf, size);
}

int main(int argc, char *argv[])
{
	int fd;
	if (argc < 2) {
		do_cat(0);
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		fd = open(argv[i], O_RDWR);
		if (fd < 0) {
			fprintf(stderr, "fopen error :%s\n", argv[i]);
			continue;
		}
		do_cat(fd);
		close(fd);
	}
}
