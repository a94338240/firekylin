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
