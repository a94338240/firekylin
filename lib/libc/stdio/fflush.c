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

int fflush(FILE *stream)
{

	if (!stream){
		for (int i = 0; i < MAX_OPEN; i++)
			if (__iotab[i]._flag)
				fflush(&__iotab[i]);
	}

	if (stream->_flag & WRITING) {
		int size = stream->_ptr - stream->_buf;
		if (size && (write(stream->_fd, stream->_buf, size) != size)) {
			stream->_flag |= _IOERR;
		}
	}

	stream->_cnt = 0;
	stream->_ptr = stream->_buf;
	stream->_flag &= ~(READING | WRITING);

	return 0;
}
