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

void *memmove(void *s1, const void *s2, size_t n)
{
	char *p1 = (char*) s1;
	char *p2 = (char*) s2;

	if(!n)
		return s1;

	if(p2<=p1 &&p2+n>p1){
		p1+=n;
		p2+=n;
		while(n--){
			*--p1=*--p2;
		}
	}else{
		while(n--){
			*p1++=*p2++;
		}
	}

	return s1;
}
