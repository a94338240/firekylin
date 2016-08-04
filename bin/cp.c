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
#include <string.h>

char buf[1024];

int main(int argc, char **argv)
{
	int fd1, fd2, size;

	if (argc < 3) {
		fprintf(stderr, "Usage:cp src dst\n");
		_exit(0);
	}

	fd1 = open(argv[1], O_READ, 0);
	if (fd1 < 0) {
		fprintf(stderr, "file open error:%s", argv[1]);
		_exit(0);
	}

	fd2 = open(argv[2], O_WRITE, 0);
	if (fd2 < 0) {
		fprintf(stderr, "file open error:%s", argv[2]);
		_exit(0);
	}

	while ((size = read(fd1, buf, 1024))) {
		write(fd2, buf, size);
	}
}
