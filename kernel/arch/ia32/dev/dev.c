/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <firekylin/driver.h>

extern void tty_init(void);
extern void mem_init(void);
extern void rd_init(void);
extern void hd_init(void);

struct char_device  *char_table[DEV_CHAR_MAX + 1];
struct block_device *blk_table[DEV_BLK_MAX + 1];

void dev_init(void)
{
	/* init char dev */
	tty_init();
	mem_init();

	/* init block dev */
	rd_init();
	hd_init();
}
