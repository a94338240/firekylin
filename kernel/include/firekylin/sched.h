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

#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>
#include <sys/param.h>
#include <signal.h>

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
