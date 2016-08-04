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
#include <sys/wait.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>
#include <errno.h>

long sys_waitpid(pid_t pid, long *status, int options)
{
	long ret;
	struct task *current = CURRENT_TASK();

	while (1) {
		for (int i = 0; i < NR_TASK; i++) {
			if (!task_table[i])
				continue;
			if (task_table[i] == current)
				continue;
			if (task_table[i]->parent != current)
				continue;

			if (pid > 0) {
				if (task_table[i]->pid != pid)
					continue;
			} else if (pid == 0) {
				if (task_table[i]->grp != current->grp)
					continue;
			} else if (pid < -1) {
				if (task_table[i]->grp != -pid)
					continue;
			}

			switch (task_table[i]->state) {
			case TASK_STATE_STOP:
				if (options & WUNTRACED) {
					if (status)
						*status = 0x7f;
					return task_table[i]->pid;
				}
				break;
			case TASK_STATE_EXIT:
				current->cutime = task_table[i]->utime;
				current->cstime = task_table[i]->stime;
				ret = task_table[i]->pid;
				if (status)
					*status = task_table[i]->status;
				put_page(__pa(task_table[i]));
				task_table[i] = NULL;
				return ret;
			default:
				continue;
			}
		}

		if (options & WNOHANG)
			return -ERSCH;

		sleep_on(NULL, TASK_STATE_PAUSE);
		if (current->sigarrive & ~(1 << (SIGCHLD - 1)))
			return -EINTR;
	}
}
