/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#include <sys/types.h>

#ifndef __PTRDIFF_T
#define __PTRDIFF_T
typedef long ptrdiff_t;
#endif

#ifndef __WCHAR_T
#define __WCHAR_T
typedef short wchar_t;
#endif

#define offestof(type,member) ((size_t)&((type*)0->member))

#endif
