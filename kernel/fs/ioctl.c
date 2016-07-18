/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <kernel.h>
#include <driver.h>
#include <fs.h>

static long char_ioctl(dev_t dev, long cmd, long arg)
{
	int major = MAJOR(dev);

	if (major > DEV_CHAR_MAX || !char_table[major]) {
		printk("dev not exist:%x", dev);
		return -ENODEV;
	}
	if (char_table[major]->ioctl)
		return char_table[major]->ioctl(dev, cmd, arg);
	return -1;
}

static long blk_ioctl(dev_t dev, long cmd, long arg)
{
	int major = MAJOR(dev);

	if (major > DEV_BLK_MAX || !blk_table[major]) {
		printk("dev not exist:%x", dev);
		return -ENODEV;
	}
	if (blk_table[major]->ioctl)
		return blk_table[major]->ioctl(dev, cmd, arg);
	return -1;
}

long sys_ioctl(unsigned long fd, long cmd, long arg)
{
	struct file *file;
	struct inode *inode;
	int res;

	if (fd > NR_OPEN || !(file = (CURRENT_TASK() )->file[fd]))
		return -EBADF;

	inode = file->f_inode;

	res = -EINVAL;
	if (S_ISCHR(inode->i_mode))
		res = char_ioctl(inode->i_rdev, cmd, arg);
	if (S_ISBLK(inode->i_mode))
		res = blk_ioctl(inode->i_rdev, cmd, arg);

	return res;
}
