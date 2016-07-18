/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <ctype.h>

unsigned char __ctype[]={ 0,
	_C,_C,_C,_C,_C,_C,_C,_C,
	_C,_C|_S,_C|_S,_C|_S,_C|_S,_C|_S,_C,_C,
	_C,_C,_C,_C,_C,_C,_C,_C,
	_C,_C,_C,_C,_C,_C,_C,_C,
	_S,_P,_P,_P,_P,_P,_P,_P,
	_P,_P,_P,_P,_P,_P,_P,_P,
	_D,_D,_D,_D,_D,_D,_D,_D,
	_D,_D,_P,_P,_P,_P,_P,_P,
	_P,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U|_X,_U,
	_U,_U,_U,_U,_U,_U,_U,_U,
	_U,_U,_U,_U,_U,_U,_U,_U,
	_U,_U,_U,_P,_P,_P,_P,_P,
	_P,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L|_X,_L,
	_L,_L,_L,_L,_L,_L,_L,_L,
	_L,_L,_L,_L,_L,_L,_L,_L,
	_L,_L,_L,_P,_P,_P,_P,_C,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
