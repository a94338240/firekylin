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

#ifndef _NET_ETHER_H
#define _NET_ETHER_H

#define ETH_ADDR_LEN	6

struct ethhdr{
	unsigned char  eh_dst[ETH_ADDR_LEN];
	unsigned char  eh_src[ETH_ADDR_LEN];
	unsigned short eh_type;
	unsigned char  eh_data[0];	/* size 46-1500 */
};

/* Values of ethhdr->eh_type */
#define ETH_TYPE_ARP	0x0806
#define ETH_TYPE_IP	0x0800

#define ETH_HDR_LEN	14

#define ETH_MTU		1500
#define ETH_VLAN_LEN	4
#define ETH_CRC_LEN	4

#define ETH_PKT_MAX_LEN	(ETH_HDR_LEN + ETH_VLAN_LEN +ETH_MTU)

#endif
