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
