/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _IA32_BITS_H
#define _IA32_BITS_H

static inline int find_bit(char *addr, int size)
{
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < 8; j++)
			if (!((*addr) & (1 << j)))
				return (i * 8 + j);
		addr++;
	}
	return -1;
}

static inline void set_bit(char *addr, int bit)
{
	*(addr + bit / 8) = *(addr + bit / 8) | (1 << (bit % 8));
}

static inline void clr_bit(char *addr, int bit)
{
	*(addr + bit / 8) = *(addr + bit / 8) & (~(1 << (bit % 8)));
}

static inline short bswapw(short data)
{
	short res;
	__asm__("bswap %%eax" :"=a"(res): "a"(data<<16));
	return res;
}

static inline int bswapl(int data)
{
	int res;
	__asm__("bswap %%eax" :"=a"(res): "a"(data));
	return res;
}

#endif
