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

#include <sys/unistd.h>
#include <sys/stat.h>
#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <errno.h>

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
