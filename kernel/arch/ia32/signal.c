/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <lock.h>
#include <sys/signal.h>
#include <arch/ia32/sched.h>
#include <arch/ia32/trap.h>

void do_signal(long unused)
{
	struct trapframe *tf = (struct trapframe *) &unused;
	struct task * current;
	sigset_t signal;

	if (!(tf->cs & 3))
		return;

	current = CURRENT_TASK();

	signal = current->sigarrive & (~current->sigmask);
	if (!signal)
		return;

	for (int signr = 0; signr < NR_SIG; signr++) {
		if (!(signal & (1 << signr)))
			continue;
		if (current->sighandle[signr] == SIG_IGN)
			continue;
		if (!current->sighandle[signr]) {
			if (signr == SIGCHLD - 1)
				continue;
			else
				do_exit(1 << signr);
		}

		unsigned long *esp = (unsigned long *) tf->esp;
		*(--esp) = tf->eax;
		*(--esp) = signr + 1;
		*(--esp) = tf->eip;
		tf->eip = (unsigned long) current->sighandle[signr];
		tf->esp = (unsigned long) esp;
		current->sigarrive &= ~(1 << signr);
		return;
	}

	current->sigarrive &= ~signal;
}
