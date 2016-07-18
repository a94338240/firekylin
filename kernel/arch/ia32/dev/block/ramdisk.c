/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <lock.h>
#include <sched.h>
#include <driver.h>
#include <mm.h>
#include <fs.h>

/*
 * ramdisk start at phyiscal address:0x200000 len:0x400000
 * it will load a ramdisk by GRUB.
 */
static unsigned long rd_start = __va(0x200000);
static unsigned long rd_sectors = 0x400000 / 512;
static sleeplock_t rd_lock;

#define lock_rd()	require_lock(&rd_lock)
#define unlock_rd()	release_lock(&rd_lock)

static void rd_read(struct buffer *buffer)
{
	char *start = (char*) rd_start + buffer->b_block * 1024;
	if (MINOR(buffer->b_dev) != 0
			|| buffer->b_block >= rd_sectors / 2)
		panic("Ramdisk Read Error : dev=%d,block=%d", buffer->b_dev,
				buffer->b_block);
	lock_rd();
	memcpy(buffer->b_data, start, 1024);
	buffer->b_flag = B_VALID;
	unlock_buffer(buffer);
	unlock_rd();
}

static void rd_write(struct buffer *buffer)
{
	char *start = (char*) rd_start + buffer->b_block * 1024;
	if (MINOR(buffer->b_dev) != 0
			|| buffer->b_block >= rd_sectors / 2)
		panic("Ramdisk Write Error : dev=%d,block=%d", buffer->b_dev,
				buffer->b_block);
	lock_rd();
	memcpy(start, buffer->b_data, 1024);
	buffer->b_flag = B_VALID;
	unlock_buffer(buffer);
	unlock_rd();
}

static struct block_device rd =
	{ "Ramdisk", NULL, NULL, rd_read, rd_write, NULL };

void rd_init(void)
{
	blk_table[DEV_BLK_RAMDISK] = &rd;
}
