/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char *envp[] = { "PATH=/bin:/test", NULL };

char *ttys[] = { "/dev/tty1", "/dev/tty2", "/dev/com1", NULL };

int main(int argc, char **argv)
{
	char **p = ttys;

	while (*p) {
		if (!fork()) {
			close(0);
			close(1);
			close(2);
			setsid();
			if (open(*p, O_RDWR, 0) < 0)
				exit(0);
			dup(0);
			dup(0);
			execve("/bin/sh", NULL, envp);
		}
		p++;
	}

	wait(NULL);
}
