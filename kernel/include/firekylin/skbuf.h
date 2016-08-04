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
