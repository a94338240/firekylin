/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SKBUF_H
#define _SKBUF_H

#include <net/arp.h>
#include <net/ip.h>
#include <net/icmp.h>
#include <net/igmp.h>
#include <net/tcp.h>
#include <net/udp.h>

struct skbuf{
	struct skbuf  *next;
	struct ethhdr *eh;
	union{
		struct iphdr *ip;
		struct arphdr *arp;
	};
	union{
		struct icmphdr *icmp;
		struct igmphdr *igmp;
		struct udphdr  *udp;
		struct tcphdr  *tcp;
	};
	unsigned char data[0];
};

extern void free_skbuf(struct skbuf *skb);
extern struct skbuf *alloc_skbuf(void);

#endif
