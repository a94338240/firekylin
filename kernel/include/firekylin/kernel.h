/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _KERNEL_H
#define _KERNEL_H

#include <sys/types.h>
#include <sys/param.h>
#include <firekylin/sched.h>

#define max(a,b)	((a)>=(b) ? (a) : (b))
#define min(a,b)	((a)<=(b) ? (a) : (b))

static inline void memset(void *s, int c, size_t size)
{
	__asm__("rep stosb" ::"D"(s), "a"(c), "c"(size));
}

static inline void memcpy(void *dst, void *src, size_t size)
{
	__asm__("rep movsb":: "D"(dst), "S"(src), "c"(size));
}

extern size_t strlen(char *s);
extern int    strcmp(char *s1, char *s2);
extern int    strncmp(char *s1, char *s2, size_t n);
extern char * strncpy(char *dst, char *src, size_t n);

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

extern time_t start_time;
extern clock_t click;

#define current_time()	(start_time + click / HZ)

extern void do_exit(long status);

extern void ksigsend(struct task *p, int signo);

enum {
	SOFTIRQ_TIMER,
	SOFTIRQ_INET
};

extern void softirq_raise(int index, long data);
extern int  softirq_setaction(int index, void (*action)(long data));

#endif
