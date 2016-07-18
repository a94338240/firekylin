/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>
#include <sys/param.h>
#include <sys/signal.h>

#include <arch/ia32/sched.h>

struct task {
	long          kesp; 		/* kernel stack_end. 	*/
	pid_t         pid; 		/* process id.  	*/
	pid_t         grp; 		/* process group id. 	*/
	pid_t         sid; 		/* session id.  	*/
	uid_t         uid; 		/* user id. 		*/
	gid_t         gid; 		/* user group id. 	*/
	clock_t       start;		/* start time. 		*/
	clock_t       stime; 		/* system time. 	*/
	clock_t       utime; 		/* user   time. 	*/
	clock_t       cstime; 		/* child system time. 	*/
	clock_t       cutime; 		/* child user   time. 	*/
	clock_t       alarm; 		/* alarm. 		*/
	long          state; 		/* process state. 	*/
	long          count; 		/* have not used time. 	*/
	long          priority; 	/* process priority.	*/
	long          pdtr; 		/* cr3 			*/
	long          sbrk; 		/* heap end. 		*/
	long          stack; 		/* stack end. 		*/
	long 	      status; 		/* exit status. 	*/
	sigset_t      sigarrive;	/* sig arrived map 	*/
	sigset_t      sigmask;		/* sig mask    map	*/
	sigact_t      sighandle[NR_SIG];/* sig handle table	*/
	unsigned int  tty; 		/* control tty. 	*/
	struct inode *pwd; 		/* current dir inode. 	*/
	struct file  *file[NR_OPEN]; 	/* file open point. 	*/
	struct task  *parent;		/* point to father task */
	struct task  *next;		/* point to list next   */
};

/* Values of task->state */
enum {
	TASK_STATE_UNUSE, 	/* unused or creating.	*/
	TASK_STATE_READY, 	/* ready  or running.	*/
	TASK_STATE_BLOCK, 	/* wait some resource.	*/
	TASK_STATE_PAUSE, 	/* wait singal.		*/
	TASK_STATE_STOP, 	/* stop by singal etc.	*/
	TASK_STATE_EXIT, 	/* task exit.		*/
};

#define NR_PRIO		8

extern struct task * task_table[];
extern struct task * priority[];

extern void sleep_on(struct task **wait, int state);
extern void wake_up_proc(struct task *p);
extern void wake_up(struct task **wait);
extern void setpriority(int pr);
extern void sched(void);

#endif
