/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _NET_ARP_H
#define _NET_ARP_H

#include <net/ether.h>

#define	ARP_HADDR_LEN	ETH_ADDR_LEN	/* Size of Ethernet MAC address	*/
#define	ARP_PADDR_LEN	4		/* Size of IP address		*/

struct arphdr {
	unsigned short arp_hrd; 	/* format of hardware address	*/
	unsigned short arp_pro; 	/* format of protocol address	*/
	unsigned char  arp_hln; 	/* length of hardware address 	*/
	unsigned char  arp_pln; 	/* length of protocal address	*/
	unsigned short arp_op;  	/* arp/rarp operation		*/
	unsigned char  arp_sha[ARP_HADDR_LEN];
	unsigned char  arp_spa[ARP_PADDR_LEN];
	unsigned char  arp_tha[ARP_HADDR_LEN];
	unsigned char  arp_tpa[ARP_PADDR_LEN];
};

/* Values of arphdr->ah_hrd */
#define ARP_HTYPE_ETHER		1	/* Ethernet hardware type	*/

/* Values of arphdr->ah_pro */
#define ARP_PTYPE_IP		0x0800	/* IP protocol type		*/

/* Values of arphdr->ah_op    */
#define ARP_OP_REQUEST		1	/* Request op code		*/
#define ARP_OP_REPLY		2	/* Reply op code		*/

struct arpentry {
	struct aprentry *prev;
	struct aprentry *next;
	unsigned char mac[ARP_HADDR_LEN];
	unsigned char ip[ARP_PADDR_LEN];
};

#endif
