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
