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

char * strpbrk(const char *s1, const char *s2)
{
	char *ts1, *ts2;

	for (ts1 = (char*) s1; *ts1; ts1++)
		for (ts2 = (char*) s2; *ts2; ts2++)
			if (*ts1 == *ts2)
				return ts1;
	return NULL;
}
