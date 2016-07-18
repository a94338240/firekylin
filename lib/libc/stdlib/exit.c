/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdlib.h>
#include <sys/unistd.h>

typedef void (*atexit_func_t)(void);

atexit_func_t atexit_func_tab[32];
int atexit_func_num;

void exit(int exit_code)
{
	//atexit_func_t fn;
	//for (int i = 0; i < atexit_func_num; i++) {
	//	printf("\nexit3:comehere");
	//	fn = atexit_func_tab[i];
	//	(fn)();
	//}
	_exit(exit_code);
}
