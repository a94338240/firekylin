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
#include <firekylin/sched.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <firekylin/partion.h>
#include <arch/ia32/portio.h>
#include <arch/ia32/trap.h>
#include "atapi.h"

struct request {
	unsigned char busy;
	unsigned char cmd;
	unsigned char nr_sect;
	unsigned char errors;
	unsigned long start_sect;
	char *buf;
	struct buffer *bh;
	struct task *wait;
};
static struct request hd_req;

struct hd_size {
	unsigned int start_sector;
	unsigned int nr_sector;
};
static struct hd_size hd_size[5];

static void hd_out_cmd(int sector, int nr, int cmd)
{
	union {
		char arg[4];
		int sec;
	} sect;
	sect.sec = sector;
	outb(0x1f2, nr);
	outb(0x1f3, sect.arg[0]);
	outb(0x1f4, sect.arg[1]);
	outb(0x1f5, sect.arg[2]);
	outb(0x1f6, (sect.arg[3] & 0x0f) + 0xe0);
	outb(0x1f7, cmd);
}

static void ide_read(struct buffer *buffer)
{
	int minor = MINOR(buffer->b_dev);
	irq_lock();
	while (hd_req.busy)
		sleep_on(&hd_req.wait, TASK_STATE_BLOCK);
	hd_req.busy = 1;
	hd_req.cmd = WIN_READ;
	hd_req.start_sect = buffer->b_block * 2 + hd_size[minor].start_sector;
	hd_req.nr_sect = 2;
	hd_req.bh = buffer;
	hd_req.buf = buffer->b_data;
	hd_out_cmd(hd_req.start_sect, hd_req.nr_sect, WIN_READ);
	irq_unlock();
}

static void ide_write(struct buffer *buffer)
{
	char tmp;
	int minor = MINOR(buffer->b_dev);
	irq_lock();
	while (hd_req.busy)
		sleep_on(&hd_req.wait, TASK_STATE_BLOCK);
	hd_req.busy = 1;
	hd_req.cmd = WIN_WRITE;
	hd_req.start_sect = buffer->b_block * 2 + hd_size[minor].start_sector;
	hd_req.nr_sect = 2;
	hd_req.bh = buffer;
	hd_req.buf = buffer->b_data;
	hd_out_cmd(hd_req.start_sect, hd_req.nr_sect, WIN_WRITE);
	do {
		tmp = inb(HD_STATUS);
	} while ((tmp & (HD_STAT_BUSY | HD_STAT_DRQ)) != HD_STAT_DRQ);

	outsw(HD_DATA, buffer->b_data, 512);
	irq_unlock();
}

static void do_hd(struct trapframe *tf)
{
	char hd_status;

	outb(0xa0, 0x20);
	outb(0x20, 0x20);

	hd_status = inb(HD_STATUS);

	if ((hd_status & 0xf1) != 0x50) {
		printk("HD error %x", inb(HD_ERROR));
		return;
	}

	if (hd_req.cmd == WIN_READ) {
		insw(HD_DATA, hd_req.buf, 512);
		hd_req.buf += 512;
		if (--hd_req.nr_sect)
			return;
		hd_req.bh->b_flag = B_VALID;
		unlock_buffer(hd_req.bh);
		hd_req.buf = NULL;
		hd_req.busy = 0;
		hd_req.bh = NULL;
		wake_up(&(hd_req.wait));
		return;
	}

	if (hd_req.cmd == WIN_WRITE) {
		hd_req.buf += 512;
		if (--hd_req.nr_sect) {
			outsw(HD_DATA, hd_req.buf, 512);
			return;
		}
		hd_req.bh->b_flag &= ~B_DIRTY;
		unlock_buffer(hd_req.bh);
		hd_req.buf = NULL;
		hd_req.busy = 0;
		hd_req.bh = NULL;
		wake_up(&(hd_req.wait));
		return;
	}
}

static void hd_identify(void)
{
	short buf[256];
	char tmp;
	struct partition *part;

	hd_out_cmd(0, 0, WIN_IDENTIFY);

	if (inb(HD_STATUS) == 0 || inb(HD_STATUS) == 0xffffffff) {
		printk("HD Control not exsit");
		return;
	}

	do {
		tmp = inb(HD_STATUS);
	} while ((tmp & (HD_STAT_BUSY | HD_STAT_DRQ)) != HD_STAT_DRQ);
	insw(0x1f0, (char*) buf, 512);

	hd_size[0].start_sector = 0;
	hd_size[0].nr_sector = buf[60] | buf[61] << 16;

	hd_out_cmd(0, 1, WIN_READ);
	do {
		tmp = inb(HD_STATUS);
	} while ((tmp & (HD_STAT_BUSY | HD_STAT_DRQ)) != HD_STAT_DRQ);
	insw(0x1f0, (char*) buf, 512);

	/*
	 * Note: here don't check the partion available.
	 */
	part = (struct partition *) ((char*) buf + 0x1be);
	printk("IDE disk partion:\n");
	for (int i = 0; i < 4; i++) {
		printk("\tpart%d: start:%d,size:%d\n", i, part->start_sect,
				part->nr_sects);
		hd_size[i + 1].start_sector = part->start_sect;
		hd_size[i + 1].nr_sector = part->nr_sects;
		part++;
	}
}

static struct block_device ide =
	{ "ATAPI", NULL, NULL, ide_read, ide_write, NULL };

void hd_init(void)
{
	hd_identify();
	set_trap_handle(0x2e, do_hd);
	outb(0xa1, inb(0xa1) & 0xbf);
	blk_table[DEV_BLK_ATAPI] = &ide;
}
