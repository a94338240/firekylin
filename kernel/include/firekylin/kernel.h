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
