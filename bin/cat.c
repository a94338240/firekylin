/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
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
	}
}
