/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _PARTION_H
#define _PARTION_H

struct partition {
	unsigned char boot_ind;
	unsigned char head;
	unsigned char sector;
	unsigned char cyl;
	unsigned char sys_ind;
	unsigned char end_head;
	unsigned char end_sector;
	unsigned char end_cyl;
	unsigned int  start_sect;
	unsigned int  nr_sects;
};

#endif
