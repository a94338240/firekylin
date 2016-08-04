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
#include <firekylin/timer.h>
#include <firekylin/lock.h>

static struct timer *timer_list = NULL;

void add_timer(struct timer *timer_ptr)
{
	struct timer *tmp = timer_list;

	irq_lock();
	if (!timer_list) {
		timer_list = timer_ptr;
		timer_ptr->next = NULL;
		irq_unlock();
		return;
	}

	while (tmp->next && (tmp->next->time < timer_ptr->time))
		tmp = tmp->next;
	timer_ptr->next = tmp->next;
	tmp->next = timer_ptr;
	irq_unlock();
}

void del_timer(struct timer *timer_ptr)
{
	struct timer *tmp = timer_list;

	irq_lock();
	if (timer_list == timer_ptr) {
		timer_list = timer_ptr->next;
		return;
	}
	while (tmp->next && (tmp->next != timer_ptr))
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	irq_unlock();
}

static void timer_softirq_action(long unused)
{
	if (!timer_list) {
		printk("timer_list is NULL");
		return;
	}

	(timer_list->func)(timer_list->data);
	timer_list = timer_list->next;
}

void do_timer(void)
{
	if (!timer_list)
		return;
	if (click >= timer_list->time)
		softirq_raise(SOFTIRQ_TIMER, (long) 0);
}

void timer_init(void)
{
	softirq_setaction(SOFTIRQ_TIMER, &timer_softirq_action);
}
