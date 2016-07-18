/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE (80*18*2*512)

void copy_file(FILE *img, FILE *sys)
{
	char buf[512];
	for (int i = 1; i < 80; i++) {
		fseek(img, 18 * 2 * 512 * i, 0);
		for (int j = 0; j < 18; j++) {
			if (fread(buf, 1, 512, sys))
				fwrite(buf, 1, 512, img);
			else
				return;
		}
	}
}

int main(int argc, char **argv)
{
	FILE *boot, *sys, *img;
	char buf[512];

	if (argc != 4) {
		fprintf(stderr, "Usage: build boot system image\n");
		exit(0);
	}

	boot = fopen(argv[1], "rb");
	if (boot == NULL) {
		fprintf(stderr, "File Open Error:%s", argv[1]);
		exit(0);
	}

	sys = fopen(argv[2], "rb");
	if (sys == NULL) {
		fprintf(stderr, "File Open Error:%s", argv[2]);
		exit(0);
	}

	img = fopen(argv[3], "wb");
	if (img == NULL) {
		fprintf(stderr, "File Open Error:%s", argv[3]);
		exit(0);
	}

	fread(buf, 512, 1, boot);
	fwrite(buf, 512, 1, img);

	copy_file(img, sys);

	fseek(img, SIZE - 1, 0);
	fputc(0, img);

	fclose(img);
}
