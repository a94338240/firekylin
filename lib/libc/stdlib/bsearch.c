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

#include <stdlib.h>
#include <sys/types.h>

void *bsearch(const void *key, const void *buf, size_t num, size_t size,
		int (*compare)(const void *, const void*))
{
	size_t l, r, idx;
	const char *p;
	int cmp;

	l = 0;
	r = num - 1;
	while (l <= r) {
		idx = (l + r) / 2;
		p = (char*) ((const char*) buf + idx * size);
		cmp = (*compare)(key, p);
		if (cmp < 0) {
			if (idx == 0)
				return NULL;
			r = idx - 1;
		} else if (cmp > 0) {
			l = idx + 1;
		}
		return (void*) p;
	}
	return NULL;
}
