/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <kernel.h>
#include <sched.h>
#include <mm.h>
#include <fs.h>

long sys_wait(pid_t pid, long *status, int options)
{
	long ret;
	struct task *current = CURRENT_TASK();

	while (1) {
		for (int i = 0; i < NR_TASK; i++) {
			if (!task_table[i]
				|| task_table[i]->state != TASK_STATE_EXIT
				|| task_table[i]->parent->pid != current->pid) {
				continue;
			}
			ret = task_table[i]->pid;
			if (status) {
				*status = task_table[i]->status;
			}
			put_page(__pa((long )task_table[i]));
			task_table[i] = NULL;
			return ret;
		}
		sleep_on(NULL, TASK_STATE_PAUSE);
	}
	return pid;
}
