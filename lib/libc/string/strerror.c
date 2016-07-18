/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <string.h>

static char *err_str[]={
	"unknown error",
	"generic error",
	"operation not permitted",
	"no such file or directory",
	"interrupted function call",
	"input/output error",
	"arg list too long",
	"is a directory",
	"invalid argument",
	"permission denied",
	"bad file descriptor",
	"not a directory",
	"not enough space",
	"resource temporarily unavailable",
	"exec format error",
	"no such device",
	"too many open files",
	"18.",
	"19.",
	"20.",
	"21.",
	"22.",
	"23.",
	"24.",
	"25.",
};

char *strerror(int errno)
{
	if ( errno <0 || errno > sizeof(err_str) / sizeof(char *)) {
		return err_str[0];
	}
	return err_str[errno];
}
