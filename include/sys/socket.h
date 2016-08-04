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

#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#define PF_LOCAL	1
#define PF_INET		2

#define AF_LOCAL	PF_LOCAL
#define AF_INET		PF_INET

struct sockaddr{
	unsigned char  sa_len;
	unsigned char  sa_family;
	char           sa_data[14];
};

struct sockaddr_in{
	unsigned char  sin_len;
	unsigned char  sin_family;
	unsigned short sin_port;
	unsigned int   sin_addr;
	unsigned char  sin_zero[8];
};

struct sockaddr_un{
	unsigned char  sun_len;
	unsigned char  sun_family;
	unsigned char  sun_path[108];
};

#endif
