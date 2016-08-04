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

#ifndef _DRIVER_H
#define _DRIVER_H

#include <sys/types.h>
#include <firekylin/fs.h>

#define DEV(major,minor)	(((major<<8)&0xff00) |((minor)&0xff))
#define MAJOR(dev)		(((dev)>>8)&0xff)
#define MINOR(dev)		((dev)&0xff)

#define DEV_CHAR_MAX		3
#define DEV_CHAR_MEM		1
#define DEV_CHAR_TTY		2

#define DEV_BLK_MAX		3
#define DEV_BLK_RAMDISK		1
#define DEV_BLK_FLOPPY		2
#define DEV_BLK_ATAPI		3

#define ROOT_DEV		DEV(DEV_BLK_RAMDISK,0)

struct char_device {
	char *name;
	int  (*open)(dev_t dev);
	int  (*close)(dev_t dev);
	int  (*read)(dev_t dev, char *buf, off_t off,size_t size);
	int  (*write)(dev_t dev, char *buf, off_t off,size_t size);
	int  (*ioctl)(dev_t dev, int cmd, long arg);
};

struct block_device {
	char *name;
	int  (*open)(dev_t dev);
	int  (*close)(dev_t dev);
	void (*read)(struct buffer *buffer);
	void (*write)(struct buffer *buffer);
	int  (*ioctl)(dev_t dev, int cmd, long arg);
};

extern struct char_device  *char_table[];
extern struct block_device *blk_table[];

#endif
