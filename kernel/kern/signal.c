/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <sched.h>
#include <sys/signal.h>
#include <sys/errno.h>

void sigsend(struct task *p, int signo)
{
	if (!p)
		return;

	p->sigarrive |= 1 << (signo - 1);
	if (p->state == TASK_STATE_PAUSE)
		wake_up_proc(p);
}

long sys_sigsend(pid_t pid, unsigned int signo)
{
	struct task **p;

	if (signo > NR_SIG)
		return -EINVAL;

	if (pid > 0) {
		for (p = task_table; p < task_table + NR_TASK; p++) {
			if (*p && (*p)->pid == pid)
				sigsend(*p, signo);
		}
	}

	if (pid < 0) {
		pid = -pid;
		for (p = task_table; p < task_table + NR_TASK; p++) {
			if (*p && (*p)->grp == pid)
				sigsend(*p, signo);
		}
	}
	return 0;
}

long sys_sigmask(long how, sigset_t *set, sigset_t *oset)
{
	struct task *current = CURRENT_TASK();

	if (oset)
		*oset = current->sigmask;

	if (!set)
		return -ERROR;

	switch (how) {
	case SIG_BLOCK:
		current->sigmask |= *set;
		break;
	case SIG_UNBLOCK:
		current->sigmask &= ~(*set);
		break;
	case SIG_SETMASK:
		current->sigmask = *set;
		break;
	default:
		return -EINVAL;
	}
	current->sigmask &= ~(1 << (SIGKILL - 1) | 1 << (SIGSTOP - 1));

	return 0;
}

long sys_sigact(unsigned long signo, sigact_t sigact)
{
	struct task *current;
	sigact_t oact;

	if (signo >= NR_SIG)
		return -EINVAL;

	current = CURRENT_TASK();

	oact = current->sighandle[signo - 1];
	current->sighandle[signo - 1] = sigact;

	return (long) oact;
}
