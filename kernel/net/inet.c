/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <lock.h>
#include <mm.h>
#include <skbuf.h>
#include <arch/ia32/bits.h>

void inet_softirq_action(long data)
{
	struct skbuf *skb=(struct skbuf *)data;

	if(!skb)
		return;

	// struct ethhdr *eh = (struct ethhdr *)skb->data;
	// printk("dst: %x:%x:%x:%x:%x:%x\n", eh->eh_dst[0], eh->eh_dst[1],
			// eh->eh_dst[2], eh->eh_dst[3], eh->eh_dst[4],
			// eh->eh_dst[5]);
	// printk("src: %x:%x:%x:%x:%x:%x\n", eh->eh_src[0], eh->eh_src[1],
			// eh->eh_src[2], eh->eh_src[3], eh->eh_src[4],
			// eh->eh_src[5]);
	// switch (bswapw(eh->eh_type)) {
	// case 0x0800:
		// printk("ip");
		// break;
	// case 0x0806:
		// printk("arp");
		// struct arphdr *ah = (struct arphdr *) eh->eh_data;
		// printk("htype:%x\n", bswapw(ah->arp_hrd));
		// printk("ptype:%x\n", bswapw(ah->arp_pro));
		// printk("haddr_len:%x\n", ah->arp_hln);
		// printk("paddr_len:%x\n", ah->arp_pln);
		// printk("src_haddr:%x:%x:%x:%x:%x:%x", ah->arp_sha[0],
				// ah->arp_sha[1], ah->arp_sha[2],
				// ah->arp_sha[3], ah->arp_sha[4],
				// ah->arp_sha[5]);
		// printk("src_paddr:%d.%d.%d.%d", ah->arp_spa[0],
				// ah->arp_spa[1], ah->arp_spa[2],
				// ah->arp_spa[3]);
		// printk("target_haddr:%x:%x:%x:%x:%x:%x", ah->arp_tha[0],
				// ah->arp_tha[1], ah->arp_tha[2],
				// ah->arp_tha[3], ah->arp_tha[4],
				// ah->arp_tha[5]);
		// printk("target_paddr:%d.%d.%d.%d", ah->arp_tpa[0],
				// ah->arp_tpa[1], ah->arp_tpa[2],
				// ah->arp_tpa[3]);
		// break;
	// default:
		// printk("unknow");
	// }
	free_skbuf(skb);
}

void inet_init(void)
{
	printk("init inet\n");
	
	softirq_setaction(SOFTIRQ_INET, &inet_softirq_action);
}
