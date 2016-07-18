/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_ICMP_H
#define _NET_ICMP_H

struct icmphdr{
	unsigned char  icmp_type;
	unsigned char  icmp_unused;
	unsigned short icmp_checksum;
	unsigned char  icmp_data[0];
};

#endif
