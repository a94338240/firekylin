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
#include <arch/ia32/trap.h>
#include <arch/ia32/portio.h>

#define LATCH		(1193180/HZ)

static void do_clock(struct trapframe *tf)
{
	extern void do_timer(void);
	struct task *current = CURRENT_TASK();

	outb(0x20, 0x20);
	click++;

	if (tf->cs & 3) {
		current->utime++;
	} else
		current->stime++;

	do_timer();

	if (--current->count < 0)
		sched();
}

void sched_init(void)
{
	struct task *current = CURRENT_TASK();

	memset(current, 0, sizeof(struct task));
	current->count = 20;
	current->state = TASK_STATE_READY;
	task_table[0] = current;
	current->priority = NR_PRIO - 1;
	current->parent = current;
	current->next = NULL;
	priority[NR_PRIO - 1] = current;

	/* setup clock */
	outb(0x43, 0x36);
	outb(0x40, LATCH && 0xff);
	outb(0x40, LATCH >> 8);
	set_trap_handle(0x20, &do_clock);
	outb(0x21, inb(0x21) & ~1);
}
