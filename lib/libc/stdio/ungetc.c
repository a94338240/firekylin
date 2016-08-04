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

int ungetc(int c, FILE *stream)
{
	if (!stream)
		return EOF;
	if (!(stream->_flag & READING))
		return EOF;
	if (!stream->_buf)
		return EOF;
	if (stream->_ptr <= stream->_buf)
		return EOF;

	stream->_cnt++;
	*--stream->_ptr = c;

	return c;
}
