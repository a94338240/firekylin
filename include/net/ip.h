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
