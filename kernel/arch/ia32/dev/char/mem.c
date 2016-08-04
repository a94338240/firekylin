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

#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/mm.h>
#include <arch/ia32/portio.h>
#include <errno.h>

/* minor dev suport by mem */
#define MEM_MEM		1
#define MEM_PORT	2
#define MEM_NULL	3
#define MEM_FULL	4

#define MEM_READ	1
#define MEM_WRITE	2

static int mem_ram(int rw, char *buf, off_t off, size_t size)
{
	char *tmp = (char*) __va(off);
	if (rw == MEM_READ)
		memcpy(buf, tmp, size);
	else
		memcpy(tmp, buf, size);
	return size;
}

static int mem_port(int rw, char *buf, off_t off, size_t size)
{
	int left = size;
	while (left-- && off < 0xffff) {
		if (rw == MEM_READ)
			*buf++ = inb(off++);
		else
			outb(off++, *buf++);
	}
	return size - left;
}

static int mem_null(int rw, char *buf, off_t off, size_t size)
{
	if (rw == MEM_READ)
		return 0;
	else
		return size;
}

static int mem_full(int rw, char *buf, off_t off, size_t size)
{
	if (rw == MEM_READ) {
		memset(buf, 0, size);
		return size;
	} else
		return -ENOSPACE;
}

static int mem_read(dev_t dev, char * buf, off_t off, size_t size)
{
	switch (MINOR(dev)) {
	case MEM_MEM:
		return mem_ram(MEM_READ, buf, off, size);
	case MEM_PORT:
		return mem_port(MEM_READ, buf, off, size);
	case MEM_NULL:
		return mem_null(MEM_READ, buf, off, size);
	case MEM_FULL:
		return mem_full(MEM_READ, buf, off, size);
	default:
		return -EIO;
	}
}

static int mem_write(dev_t dev, char * buf, off_t off, size_t size)
{
	switch (MINOR(dev)) {
	case MEM_MEM:
		return mem_ram(MEM_WRITE, buf, off, size);
	case MEM_PORT:
		return mem_port(MEM_WRITE, buf, off, size);
	case MEM_NULL:
		return mem_null(MEM_WRITE, buf, off, size);
	case MEM_FULL:
		return mem_full(MEM_WRITE, buf, off, size);
	default:
		return -EIO;
	}
}

static struct char_device mem =
	{ "mem", NULL, NULL, mem_read, mem_write, NULL };

void mem_init(void)
{
	char_table[DEV_CHAR_MEM] = &mem;
}
