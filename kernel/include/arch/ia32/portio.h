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

#ifndef _IA32_PORTIO_H
#define _IA32_PORTIO_H

static inline char inb(short port)
{
	char res;
	__asm__("inb %%dx,%%al" :"=a"(res) :"d"(port));
	return res;
}

static inline short inw(short port)
{
	short res;
	__asm__("inw %%dx,%%ax" :"=a"(res) :"d"(port));
	return res;
}

static inline int inl(short port)
{
	int res;
	__asm__("inl %%dx,%%eax" :"=a"(res) :"d"(port));
	return res;
}

static inline void outb(short port, char data)
{
	__asm__("outb %%al,%%dx" ::"a"(data), "d"(port));
}

static inline void outw(short port, short data)
{
	__asm__("outw %%ax,%%dx" ::"a"(data), "d"(port));
}

static inline void outl(short port, int data)
{
	__asm__("outl %%eax,%%dx" ::"a"(data), "d"(port));
}

static inline void insb(short port, void *buf, int size)
{
	__asm__("rep insb" :: "D"(buf),"d"(port),"c"(size));
}

static inline void insw(short port, void *buf, int size)
{
	__asm__("rep insw" :: "D"(buf),"d"(port),"c"(size>>1));
}

static inline void insl(short port, void *buf, int size)
{
	__asm__("rep insl" :: "D"(buf), "d"(port), "c"(size>>2));
}

static inline void outsb(short port, void *buf, int size)
{
	__asm__("rep outsb" :: "S"(buf),"d"(port),"c"(size));
}

static inline void outsw(short port, void *buf, int size)
{
	__asm__("rep outsw" :: "S"(buf),"d"(port),"c"(size>>1));
}

static inline void outsl(short port, void *buf, int size)
{
	__asm__("rep outsl" :: "S"(buf),"d"(port),"c"(size));
}

static inline char readcoms(char index)
{
	outb(0x70, index);
	return inb(0x71);
}

static inline void writecmos(char index, char data)
{
	outb(0x70, index);
	outb(0x71, data);
}

#endif
