/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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
