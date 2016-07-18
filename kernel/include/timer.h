/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _TIMER_H
#define _TIMER_H

struct timer{
	clock_t       time;
	void          (*func)(long arg);
	long          data;
	struct timer *next;
};

extern void add_timer(struct timer *timer_ptr);
extern void del_timer(struct timer *timer_ptr);

#endif
