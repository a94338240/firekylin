/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/types.h>
#include <sys/signal.h>
#include <errno.h>

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
