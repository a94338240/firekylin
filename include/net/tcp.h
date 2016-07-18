/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_TCP_H
#define _NET_TCP_H

struct tcphdr{
	unsigned short tcp_src;
	unsigned short tcp_dst;
	unsigned int   tcp_seq;
	unsigned int   tcp_ackseq;
	unsigned short tcp_flags;
	unsigned short tcp_window;
	unsigned short tcp_check;
	unsigned short tcp_urgptr;
	unsigned char  tcp_data[0];
};

#endif
