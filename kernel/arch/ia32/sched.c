/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <sched.h>
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
