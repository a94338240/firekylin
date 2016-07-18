/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
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
