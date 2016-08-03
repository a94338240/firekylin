/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/lock.h>

void require_lock(sleeplock_t *lock)
{
	pid_t pid = (CURRENT_TASK() )->pid;

	irq_lock();
	if (pid == lock->pid) {
		irq_unlock();
		return;
	}
	while (lock->pid)
		sleep_on(&lock->wait, TASK_STATE_BLOCK);

	lock->pid = pid;
	irq_unlock();
}

void release_lock(sleeplock_t *lock)
{
	irq_lock();
	lock->pid = 0;
	wake_up(&lock->wait);
	irq_unlock();
}
