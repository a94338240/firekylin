/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_UDP_H
#define _NET_UDP_H

struct udphdr{
	unsigned short udp_src;
	unsigned short udp_dst;
	unsigned short udp_len;
	unsigned short udp_check;
	unsigned char  udp_data[0];
};

#endif
