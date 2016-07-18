/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_IP_H
#define _NET_IP_H

struct iphdr{
	unsigned char  ip_hl_and_ver;
	unsigned char  ip_tos;
	unsigned short ip_len;
	unsigned short ip_id;
	unsigned short ip_fragoff;
	unsigned char  ip_ttl;
	unsigned char  ip_protocol;
	unsigned char  ip_checksum;
	unsigned int   ip_srcaddr;
	unsigned int   ip_dstaddr;
	unsigned char  ip_data[0];
};

#endif
