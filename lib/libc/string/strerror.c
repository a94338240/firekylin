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
