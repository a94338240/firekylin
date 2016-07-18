/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STDARG_H
#define _STDARG_H

typedef char * va_list;

#define va_start(ap,fmt)   ap=(va_list)&fmt+sizeof(int)
#define va_arg(ap,type)	  (ap+=sizeof(int),*((type*)(ap-sizeof(int))))
#define va_copy(d,s)	  (d)=(s)
#define va_end(ap)

#endif
