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
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[1024];
char buf2[1024];

int main(int argc, char **argv)
{
	int fd[2];

	pipe(&fd[0]);

	printf("fd1=%d,fd2=%d",fd[0],fd[1]);

	memset(buf,'A',1024);
	memset(buf2,'B',1024);

	if(!fork()){
		close(0);
		printf("---%d",dup(fd[0]));
		close(fd[0]);
		close(fd[1]);
		printf("in child\n");
		execve("/bin/cat",NULL,NULL);
	}
	else{
		printf("in fatrhe");

		write(fd[1],buf,1024);

		printf("father write over");
		close(fd[0]);
		close(fd[1]);
		wait(-1,NULL,0);
	}
}
