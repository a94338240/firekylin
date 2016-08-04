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

#include <stdlib.h>
#include <sys/types.h>
#include <sys/unistd.h>

#define NALLOC 	512

/*
 * size should be 16 Bytes.
 */
struct block_list {
	struct block_list *next;
	long size;
	char padding[8];
};

static struct block_list base = { NULL, 1, { 0 } };

void free(void *p)
{
	struct block_list *bp, *tmp;

	if(!p)
		return ;
	bp = (struct block_list *) p - 1;

	for (tmp = &base; tmp->next; tmp = tmp->next) {
		if (!(tmp < bp && bp < tmp->next))
			continue;

		if (bp + bp->size == tmp->next) {
			bp->size += tmp->next->size;
			bp->next = tmp->next->next;
		} else
			bp->next = tmp->next;

		if (tmp + tmp->size == bp) {
			tmp->size += bp->size;
			tmp->next = bp->next;
		} else
			tmp->next = bp;
		return;
	}

	tmp->next = bp;
	bp->next = NULL;
}

void * malloc(long nbytes)
{
	struct block_list *prev, *p;
	struct block_list *up;
	long nunits, nu;
	char *cp;

	nunits = (nbytes + sizeof(struct block_list) - 1)
			/ sizeof(struct block_list) + 1;
	repeat: for (prev = &base, p = prev->next; p; prev = p, p = p->next) {
		if (p->size < nunits)
			continue;

		if (p->size == nunits) {
			prev->next = p->next;
		} else {
			p->size -= nunits;
			p += p->size;
			p->size = nunits;
		}
		return (void*) (p + 1);
	}

	nu = nunits > NALLOC ? nunits : NALLOC;
	cp = (char*) sbrk(nu * sizeof(struct block_list));
	if (cp == (char*) -1)
		return NULL;
	up = (struct block_list *) cp;
	up->size = nu;
	up->next = NULL;

	free(up + 1);
	goto repeat;

	return NULL;
}
