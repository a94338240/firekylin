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
#include <string.h>
#include <errno.h>

static char **origenv;

int putenv(const char *string)
{
	size_t len;
	int envc;
	int remove = 0;
	char *tmp;
	char **ep;
	char **newenv;

	if (!origenv)
		origenv = environ;

	if (!(tmp = strchr(string, '='))) {
		len = strlen(string);
		remove = 1;
	} else
		len = tmp - string + 1;
	for (envc = 0, ep = environ; *ep; ++ep) {
		if (*string == **ep && !memcmp(string, *ep, len)) {
			if (remove) {
				for (; ep[1]; ++ep)
					ep[0] = ep[1];
				ep[0] = 0;
				return 0;
			}
			*ep = (char*) string;
			return 0;
		}
		++envc;
	}
	if (tmp) {
		newenv = (char**) realloc(environ == origenv ? 0 : origenv,
				(envc + 2) * sizeof(char*));
		if (!newenv)
			return -1;
		newenv[0] = (char*) string;
		memcpy(newenv + 1, environ, (envc + 1) * sizeof(char*));
		environ = newenv;
	}
	return 0;
}
