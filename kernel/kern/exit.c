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
#include <firekylin/sched.h>
#include <firekylin/lock.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>
#include <errno.h>

extern void unready(int state);
void do_exit(long exitcode)
{
	extern int sys_close(int fd);
	struct task * current = CURRENT_TASK();
	current->status = exitcode;
	free_mm();

	if (current->pwd)
		iput(current->pwd);
	for (int i = 0; i < NR_OPEN; i++)
		if (current->file[i])
			sys_close(i);

	irq_lock();
	unready(TASK_STATE_EXIT);
	ksigsend(current->parent, SIGCHLD);
	sched();
}

void sys_exit(long status)
{
	do_exit((status << 8) & 0xff00);
}
