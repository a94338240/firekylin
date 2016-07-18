/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>

void _exit(int status)
{
	__asm__("int $0x30" : :"a"(__NR_exit),"b"(status));
}
