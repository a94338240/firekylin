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
#include <firekylin/sched.h>
#include <firekylin/driver.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>

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
