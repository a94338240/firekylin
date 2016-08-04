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
#include <signal.h>
#include <errno.h>

void ksigsend(struct task *p, int signo)
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
				ksigsend(*p, signo);
		}
	}

	if (pid < 0) {
		pid = -pid;
		for (p = task_table; p < task_table + NR_TASK; p++) {
			if (*p && (*p)->grp == pid)
				ksigsend(*p, signo);
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
