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
