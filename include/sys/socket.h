/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
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
