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

FILE *fopen(const char *filename, const char *mode)
{
	int fd;
	FILE *f;

	fd = open(filename, O_RDWR | O_CREAT);
	if (fd < 0)
		return NULL;

	for (int i = 0; i < MAX_OPEN; i++) {
		if (__iotab[i]._flag)
			continue;
		f = &__iotab[i];
		f->_fd=fd;
		f->_flag=_IOFBF;
		f->_cnt=0;
		f->_bufsize=0;
		f->_buf=NULL;
		f->_ptr=NULL;
		return f;
	}
	return NULL;
}
