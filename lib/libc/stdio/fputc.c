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

int fputc(int ch, FILE *stream)
{
	if (!stream)
		return EOF;

	if (ferror(stream))
		return EOF;

	if (stream->_flag & READING)
		fflush(stream);

	if (stream->_cnt <= 0) {

		stream->_flag |=WRITING;

		if (!stream->_buf) {
			stream->_buf = malloc(BUFSIZ);
			if (!stream->_buf) {
				stream->_flag |= _IOERR;
				return EOF;
			}
			stream->_bufsize = BUFSIZ;
			stream->_ptr = stream->_buf;
		}

		int tmp = stream->_ptr - stream->_buf;
		if (tmp > 0) {
			if (write(stream->_fd, stream->_buf, tmp) != tmp) {
				stream->_flag |= _IOERR;
				return EOF;
			}
		}
		stream->_cnt = stream->_bufsize;
		stream->_ptr = stream->_buf;
	}

	stream->_cnt--;
	*stream->_ptr++ = ch;

	return ch;
}
