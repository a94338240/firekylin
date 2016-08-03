/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/lock.h>
#include <firekylin/mm.h>
#include <firekylin/skbuf.h>

static struct skbuf *skb_free_list;

void free_skbuf(struct skbuf *skb)
{
	if (!skb)
		return;

	irq_lock();
	skb->next = skb_free_list;
	skb_free_list = skb;
	irq_unlock();
}

struct skbuf *alloc_skbuf(void)
{
	unsigned long tmp;
	struct skbuf *skb;

	irq_lock();
	if (skb_free_list) {
		skb = skb_free_list;
		skb_free_list = skb_free_list->next;
		irq_unlock();
		return skb;
	}
	irq_unlock();

	tmp = __va(get_page());

	free_skbuf((struct skbuf *) (tmp + 2048));

	return (struct skbuf*) tmp;
}
