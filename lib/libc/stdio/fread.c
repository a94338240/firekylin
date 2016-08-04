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

#include "stdio_loc.h"

size_t fread(void * ptr, size_t size, size_t nobj, FILE *stream)
{
	int tmp_len, done, c;
	char *buf = (char*) ptr;

	tmp_len = size * nobj;
	if (!tmp_len)
		return 0;

	while (tmp_len--) {
		c = fgetc(stream);
		if (c == EOF)
			break;
		*buf++ = c;
		done++;
	}

	return done / size;
}
