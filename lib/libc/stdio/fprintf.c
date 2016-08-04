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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int fprintf(FILE *stream, const char *fmt, ...)
{
	va_list ap;
	int i;
	char buf[512];

	fflush(stream);

	i=vsnprintf(buf,512,fmt,va_start(ap,fmt));
	write(fileno(stream),buf,i);

	return i;
}
