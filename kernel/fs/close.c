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

#include <sys/stat.h>
#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <errno.h>

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
