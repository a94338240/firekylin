/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/param.h>
#include <kernel.h>
#include <sched.h>
#include <driver.h>
#include <mm.h>
#include <fs.h>

#define READ_BUF	1
#define WRITE_BUF	2

static struct buffer buffer_table[NR_BUFFER];
static struct buffer *free_list_head;
static sleeplock_t buffer_table_lock;

#define lock_buffer_table()	require_lock(&buffer_table_lock)
#define unlock_buffer_table()	release_lock(&buffer_table_lock)

static void rw_block(int cmd, struct buffer* buf)
{
	int major = MAJOR(buf->b_dev);
	if (major > DEV_BLK_MAX || !blk_table[major])
		panic("dev %x not exsit", buf->b_dev);
	if (cmd == READ_BUF)
		blk_table[major]->read(buf);
	else
		blk_table[major]->write(buf);
}

static struct buffer * getblk(dev_t dev, int block)
{
	struct buffer *buf;

	lock_buffer_table();
	buf = buffer_table;
	while (buf < buffer_table + NR_BUFFER) {
		if ((buf->b_dev == dev) && (buf->b_block == block)) {
			buf->b_count++;
			unlock_buffer_table();
			lock_buffer(buf);
			return buf;
		}
		buf++;
	}

	if (!free_list_head) {
		/*
		 * dump buffer state
		 */
		for (struct buffer *buf = buffer_table;
				buf < buffer_table + NR_BUFFER; buf++) {
			printk("%x:%d-%d-%x\t", buf->b_dev, buf->b_block,
					buf->b_count, buf->b_flag);
		}
		panic("No availabel buffer");
	}

	if (free_list_head == free_list_head->b_free_next) {
		buf = free_list_head;
		free_list_head = NULL;
	} else {
		buf = free_list_head;
		free_list_head = free_list_head->b_free_next;
		buf->b_free_prev->b_free_next = buf->b_free_next;
		buf->b_free_next->b_free_prev = buf->b_free_prev;
	}
	buf->b_count++;
	unlock_buffer_table();
	lock_buffer(buf);
	if (buf->b_flag & B_DIRTY)
		rw_block(READ_BUF, buf);
	buf->b_dev = dev;
	buf->b_block = block;
	buf->b_flag &= ~B_VALID;

	return buf;
}

void brelse(struct buffer *buf)
{
	if (!buf)
		return;

	lock_buffer(buf);

	if (--buf->b_count < 0) {
		printk("put_buffer:buffer_count <0");
		buf->b_count = 0;
	}

	if (buf->b_count == 0) {
		lock_buffer_table();
		if (free_list_head == NULL) {
			free_list_head = buf->b_free_next = buf->b_free_prev =
					buf;
		} else {
			buf->b_free_next = free_list_head;
			buf->b_free_prev = free_list_head->b_free_prev;
			buf->b_free_prev->b_free_next = buf;
			free_list_head->b_free_prev = buf;
		}
		unlock_buffer_table();
	}
	unlock_buffer(buf);
}

struct buffer * bread(dev_t dev, long block)
{
	struct buffer *buf = getblk(dev, block);

	if (buf == NULL)
		panic("bread:get_buffer return NULL");

	if (!(buf->b_flag & B_VALID)) {
		rw_block(READ_BUF, buf);
		/*
		 * lock buffer without to check how hold the lock.
		 * buffer would be unlock by driver.
		 */
		irq_lock();
		while (buf->b_lock.pid) {
			sleep_on(&(buf->b_lock.wait), TASK_STATE_BLOCK);
		}
		buf->b_lock.pid = (CURRENT_TASK() )->pid;
		irq_unlock();
	}
	return buf;
}

int sys_sync()
{
	extern void sync_inode();
	struct buffer *bh;

	sync_inode();
	for (bh = buffer_table; bh < buffer_table + NR_BUFFER; bh++) {
		lock_buffer(bh);
		if (bh->b_flag & B_DIRTY) {
			/*
			 *  buffer shold be unlock in write_block.
			 */
			rw_block(WRITE_BUF, bh);
			irq_lock();
			while (bh->b_lock.pid)
				sleep_on(&(bh->b_lock.wait), TASK_STATE_BLOCK);
			irq_unlock();
		}
		unlock_buffer(bh);
	}
	return 0;
}

void buffer_init(void)
{
	struct buffer *buf = buffer_table;
	char *p;

	for (int i = 0; i < NR_BUFFER; i++, buf++) {
		if ((i % 4) == 0)
			p = (char*) __va(get_page());
		buf->b_dev = 0;
		buf->b_block = 0;
		buf->b_flag = 0;
		buf->b_count = 0;
		buf->b_data = p;
		buf->b_hash_prev = NULL;
		buf->b_hash_next = NULL;
		buf->b_free_prev = buf - 1;
		buf->b_free_next = buf + 1;
		buf->b_lock.pid = 0;
		buf->b_lock.wait = NULL;
		p += BUF_SIZE;
	}

	buffer_table[0].b_free_prev = &buffer_table[NR_BUFFER - 1];
	buffer_table[NR_BUFFER - 1].b_free_next = buffer_table;
	free_list_head = buffer_table;
}
