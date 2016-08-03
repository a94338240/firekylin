/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _LOCK_H
#define _LOCK_H

#include <sys/types.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>

#define irq_disable()	__asm__("cli")

#define irq_enable() 	__asm__("sti")

/* Just should be used once in a function */
#define irq_lock()			\
    unsigned long  __flag;		\
    __asm__("pushf;popl %0;cli":"=m"(__flag))

/* Used must after irq_lock() */
#define irq_unlock()			\
    __asm__("pushl %0;popf"::"m"(__flag))

typedef struct sleeplock {
	pid_t        pid; 	/* which task hold the lock,default 0 */
	struct task *wait; 	/* task list wait for this lock       */
} sleeplock_t;

extern void require_lock(sleeplock_t *lock);
extern void release_lock(sleeplock_t *lock);

#endif
