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
