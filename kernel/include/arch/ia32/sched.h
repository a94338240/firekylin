/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _IA32_SCHED_H
#define _IA32_SCHED_H

#include <sys/types.h>

struct tss_struct {
	unsigned int  link;
	unsigned int  esp0;
	unsigned int  ss0;
	unsigned int  esp1;
	unsigned int  ss1;
	unsigned int  esp2;
	unsigned int  ss2;
	unsigned int  cr3;
	unsigned int  eip;
	unsigned int  eflags;
	unsigned int  eax;
	unsigned int  ecx;
	unsigned int  edx;
	unsigned int  ebx;
	unsigned int  esp;
	unsigned int  ebp;
	unsigned int  esi;
	unsigned int  edi;
	unsigned int  es;
	unsigned int  cs;
	unsigned int  ss;
	unsigned int  ds;
	unsigned int  fs;
	unsigned int  gs;
	unsigned int  ldt;
	unsigned short trap;
	unsigned short iobase;
};

#define CURRENT_TASK() 			\
    (struct task*)({ 			\
	unsigned long __res; 		\
	__asm__ __volatile__(		\
            "movl %%esp,%%eax;"		\
            "andl $0xfffff000,%%eax"	\
            :"=a"(__res)); 		\
	__res; 				\
    })

#define __switch_to(p)			\
    ({	tss.esp0 = (long)p + 4096;	\
        __asm__ __volatile__ (		\
        "movl %%eax,%%cr3;"		\
	"pushl $__ret_switch;"		\
	"pushf;"			\
	"pushl %%eax;"			\
	"pushl %%ebx;"			\
	"pushl %%ecx;"			\
	"pushl %%edx;"			\
	"pushl %%edi;"			\
	"pushl %%esi;"			\
	"pushl %%ebp;"			\
	"subl  $108,%%esp;"		\
	"fnsave (%%esp);"		\
	"movl  %%esp,%%eax;"		\
	"andl  $0xfffff000,%%eax;"	\
	"movl  %%esp,(%%eax);"		\
	"movl  %%ecx,%%esp;"		\
	"frstor (%%esp);"		\
	"addl  $108,%%esp;"		\
	"popl  %%ebp;"			\
	"popl  %%esi;"			\
	"popl  %%edi;"			\
	"popl  %%edx;"			\
	"popl  %%ecx;"			\
	"popl  %%ebx;"			\
	"popl  %%eax;"			\
	"popf;"				\
	"ret;"				\
	"__ret_switch:  ;"		\
	::"a"(p->pdtr),			\
	  "c"(p->kesp));		\
    })

static inline long build_context(long stack)
{
	long *p = (long *) stack;

	--p;			// ret
	*(--p) = 0x13200;	// popf
	*(--p) = 0;		// eax
	*(--p) = 0;		// ebx
	*(--p) = 0;		// ecx
	*(--p) = 0;		// edx
	*(--p) = 0;		// edi
	*(--p) = 0;		// esi
	*(--p) = 0;		// ebp

	p -= 27;
	__asm__ ("fnsave (%%eax)" ::"a"(p));

	return (long) p;
}

extern struct tss_struct tss;

#endif
