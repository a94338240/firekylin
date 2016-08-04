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
#include <firekylin/lock.h>
#include <arch/ia32/sched.h>
#include <arch/ia32/trap.h>
#include <signal.h>

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
