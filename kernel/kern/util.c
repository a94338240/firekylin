/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <firekylin/kernel.h>
#include <firekylin/lock.h>
#include <stdarg.h>

extern int vsprintf(char* buf, char* fmt, va_list ap);
extern void con_print(char *buf, int len);

static char printk_buf[512];

int printk(char* fmt, ...)
{
	va_list ap;
	int i;

	va_start(ap, fmt);
	i = vsprintf(printk_buf, fmt, ap);
	con_print(printk_buf, i);
	return i;
}

void panic(char* fmt, ...)
{
	va_list ap;
	int i;

	printk("\nKernel Panic: ");
	va_start(ap, fmt);
	i = vsprintf(printk_buf, fmt, ap);
	con_print(printk_buf, i);
	irq_disable();
	__asm__("hlt");
}
