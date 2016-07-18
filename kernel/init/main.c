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
#include <arch/ia32/portio.h>

#define BCD_BIN(c)	(c=c/16*10+c%16)

extern char _edata[];
extern char _end[];

extern void arch_init();
extern void mm_init();
extern void dev_init();
extern void pci_init();
extern void ne2k_init();
extern void buffer_init();
extern void sched_init();
extern void softirq_init();
extern void timer_init();
extern int  sys_fork();
extern int  sys_execve(char *filename, char **argv, char **envp);
extern void mount_root(void);
extern void inet_init(void);

static void time_init()
{
	extern time_t mktime(int year, int mon, int day, int hour, int min,
			int sec);
	int year, month, day, hour, min, sec;

	sec=readcoms(0);
	min=readcoms(2);
	hour=readcoms(4);
	day=readcoms(7);
	month=readcoms(8);
	year=readcoms(9);
	BCD_BIN(sec);
	BCD_BIN(min);
	BCD_BIN(hour);
	BCD_BIN(day);
	BCD_BIN(month);
	BCD_BIN(year);
	start_time = mktime(year, month, day, hour, min, sec);
}

void start(void)
{
	memset(_edata, 0, (_end - _edata));

	arch_init();
	time_init();
	dev_init();
	mm_init();
	pci_init();
	ne2k_init();
	sched_init();

	if (sys_fork()) {
		__asm__("__hlt:hlt ; jmp __hlt");
	}

	setpriority(5);

	softirq_init();
	inet_init();
	timer_init();
	buffer_init();
	mount_root();

	sys_execve("/bin/init", NULL, NULL);
	panic("Can't find init");
}
