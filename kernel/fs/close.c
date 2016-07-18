/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/stat.h>
#include <sys/errno.h>
#include <kernel.h>
#include <sched.h>
#include <driver.h>
#include <fs.h>

//extern int pipe_close(struct inode *inode);

long char_close(dev_t dev)
{
	int major = MAJOR(dev);

	if (major > DEV_CHAR_MAX || !char_table[major])
		panic("char dev not exist:%x", dev);
	if (char_table[major]->close)
		return char_table[major]->close(dev);
	return 0;
}

long blk_close(dev_t dev)
{
	int major = MAJOR(dev);

	if (major > DEV_CHAR_MAX || !blk_table[major])
		panic("block dev not exist:%x", dev);
	if (blk_table[major]->close)
		return blk_table[major]->close(dev);
	return 0;
}

long sys_close(unsigned int fd)
{
	struct file *filp;
	struct inode *inode;
	struct task *current = CURRENT_TASK();

	if (fd > NR_OPEN || !(filp = current->file[fd]))
		return -EINVAL;

	current->file[fd] = NULL;

	inode = filp->f_inode;
	if (--filp->f_count < 0)
		panic("close:file count is 0");
	if (!filp->f_count)
		iput(inode);
	return 0;
}
