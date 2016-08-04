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

FILE __iotab[MAX_OPEN] = {
	{ 0, _IOLBF, 0, 0, 0, 0 },
	{ 1, _IOLBF, 0, 0, 0, 0 },
	{ 2, _IONBF, 0, 0, 0, 0 },
};

FILE *stdin=  &__iotab[0];
FILE *stdout= &__iotab[1];
FILE *stderr= &__iotab[2];

#if 0
void dump_iotab(void)
{
	FILE *p=&__iotab[0];
	printf("dump_iotab:\n");
	printf(" idx  fd  flag  count   bufsize  buf   ptr\n");
	for(int i=0;i<MAX_OPEN; i++){
		if(p->_flag){
			printf("%5d%5d%5x%5d%5d%5x%5x\n",
				i,p->_fd, p->_flag, p->_cnt,
				p->_bufsize, p->_buf, p->_ptr);
		}
		p++;
	}
}
#endif
