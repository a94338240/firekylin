/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
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
