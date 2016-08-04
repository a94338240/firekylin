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
