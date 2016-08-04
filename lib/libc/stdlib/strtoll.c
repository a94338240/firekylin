;/*  This file is part of The Firekylin Operating System.
; *
; *  Copyright 2016 Liuxiaofeng
; *
; *  Licensed under the Apache License, Version 2.0 (the "License");
; *  you may not use this file except in compliance with the License.
; *  You may obtain a copy of the License at
; *
; *      http://www.apache.org/licenses/LICENSE-2.0
; *
; *  Unless required by applicable law or agreed to in writing, software
; *  distributed under the License is distributed on an "AS IS" BASIS,
; *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the License for the specific language governing permissions and
; *  limitations under the License.
; */

#include <stdlib.h>
#include <ctype.h>

long long strtoll(const char *str, char **endptr, int base)
{
	long long ret = 0;
	char *p = (char *) str;
	int sig = 0;

	while (isspace(*p))
		p++;
	if (*p == '-') {
		sig = 1;
		p++;
	} else {
		if (*p == '+')
			p++;
	}
	while (isdigit(*p)) {
		ret = ret * 10 + *p - '0';
		p++;
	}
	if (endptr)
		*endptr = p;

	return sig ? ret : -ret;
}
