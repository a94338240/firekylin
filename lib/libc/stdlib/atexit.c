/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdlib.h>

typedef void (*atexit_func_t)(void);

extern atexit_func_t atexit_func_tab[];
extern int atexit_func_num;

int atexit(void (*func)(void))
{
	if(atexit_func_num<32){
		atexit_func_tab[atexit_func_num++]=func;
		return 1;
	}
	return 0;
}
