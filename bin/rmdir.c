/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage:rmdir dirname");
		_exit(0);
	}
	if (rmdir(argv[1]) < 0)
		fprintf(stderr, "error:mkdir");
}
