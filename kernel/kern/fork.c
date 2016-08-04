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

#include <sys/types.h>
#include <errno.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>

static pid_t last_pid = 0;

long sys_fork(long unuesd)
{
	struct task * task;
	struct task * current;

	task = (struct task*) __va(get_page());
	current=CURRENT_TASK();
	memcpy(task, current , PAGE_SIZE);
	task->state=TASK_STATE_STOP;
	task->pid = ++last_pid;
	task->parent = current;

	task->utime=0;
	task->stime=0;
	task->cutime=0;
	task->cstime=0;
	task->start=current_time();
	task->kesp = build_context((((long) &unuesd) & 0xfff) | (long) task);
	task->pdtr = copy_mm();

	irq_lock();
	if (current->pwd)
		current->pwd->i_count++;
	for (int i = 0; i < NR_OPEN; i++) {
		if (current->file[i]) {
			current->file[i]->f_count++;
		}
	}
	irq_unlock();

	for (int i = 0; i < NR_TASK; i++) {
		if (task_table[i])
			continue;
		task_table[i] = task;
		wake_up_proc(task);
		return task->pid;
	}
	return -1;
}
