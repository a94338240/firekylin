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

#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/types.h>
#include <errno.h>

#define NR_SIG		32

#define SIGHUP		1
#define SIGINT		2
#define SIGQUIT		3
#define SIGILL		4
#define SIGTRAP		5
#define SIGABRT		6
#define SIGFPU		7
#define SIGKILL		8
#define SIGUSR1		9
#define SIGSEGV		10
#define SIGUSR2		11
#define SIGPIPE		12
#define SIGALARM	13
#define SIGTREM		14
#define SIGCHLD		15
#define SIGTKFLT	16
#define SIGCONT		17
#define SIGSTOP		18
#define SIGTSTP		19
#define SIGTTIN		20
#define	SIGTTOU		21
#define SIGTERM		22

typedef unsigned long 	sigset_t;
typedef long		(*sigact_t)(int signo, long ret);

#define SIG_BLOCK	1
#define SIG_UNBLOCK	2
#define SIG_SETMASK	3

#define SIG_ERR		((sigact_t)-1)
#define SIG_DFL		((sigact_t)0)
#define SIG_IGN		((sigact_t)1)

#define signal(a,b)

extern sigact_t sigact(int signo, sigact_t action);
extern int sigmask(int how, sigset_t *set, sigset_t *oset);
extern int sigsend(pid_t pid, int signo);
extern int raise(int signo);

static inline int sigaddset(sigset_t *set, int signo)
{
	if (signo < 0 || signo > 32) {
		errno = EINVAL;
		return -1;
	}

	*set |= 1 << (signo - 1);
	return 0;
}

static inline int sigdelset(sigset_t *set, int signo)
{
	if (signo < 0 || signo > 32) {
		errno = EINVAL;
		return -1;
	}

	*set &= ~(1 << (signo - 1));
	return 0;
}

static inline int sigismember(sigset_t *set, int signo)
{
	if (signo < 0 || signo > 32) {
		errno = EINVAL;
		return -1;
	}

	return (*set) >> (signo - 1) & 1;
}

static inline int sigemptyset(sigset_t *set)
{
	*set = 0;
	return 0;
}

static inline int sigefillset(sigset_t *set)
{
	*set = ~(sigset_t) 0;
	return 0;
}

#endif
