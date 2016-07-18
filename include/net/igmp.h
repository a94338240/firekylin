/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_IGMP_H
#define _NET_IGMP_H

struct igmphdr{
	unsigned char  igmp_type;
	unsigned char  igmp_unused;
	unsigned short igmp_checksum;
	unsigned long  igmp_group;
	unsigned char  igmp_data[0];
};

#endif
