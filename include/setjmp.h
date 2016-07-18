/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SETJMP_H
#define _SETJMP_H

typedef long jmp_buf[6];

extern int  setjmp(jmp_buf buf);
extern void longjmp(jmp_buf buf, int val);

#endif
