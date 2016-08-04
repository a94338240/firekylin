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

#define NR_SOFTIRQ	16

struct softirq_action {
	void (*action)(long data);
	long data;
};

unsigned long softirq_map;
struct softirq_action softirq_actions[NR_SOFTIRQ];

struct task *softirq_wait;

void softirq_raise(int index, long data)
{
	if (index >= NR_SOFTIRQ)
		return;
	irq_lock();
	softirq_map |= 1 << index;
	softirq_actions[index].data=data;
	irq_unlock();
	wake_up(&softirq_wait);
}

int softirq_setaction(int index, void (*action)(long data))
{
	if (index > NR_SOFTIRQ)
		panic("set_sofirq_action index too big %d", index);

	if (softirq_actions[index].action != NULL)
		panic("set_softirq_action action has exsit %d", index);

	softirq_actions[index].action = action;

	return 0;
}

extern long sys_fork(void);

void do_softirq(void)
{
	setpriority(1);

	while (1) {
		while (!softirq_map)
			sleep_on(&softirq_wait, TASK_STATE_BLOCK);

		for (int i = 0; i < NR_SOFTIRQ; i++) {
			if (!(softirq_map & (1 << i)))
				continue;
			irq_lock();
			softirq_map &= ~(1 << i);
			irq_unlock();
			(softirq_actions[i].action)(softirq_actions[i].data);
		}
	}
}

void softirq_init(void)
{
	printk("init softirq\n");

	if (!sys_fork())
		do_softirq();
}
