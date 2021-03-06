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
#include <firekylin/fs.h>
#include <errno.h>

static void copy_stat(struct inode *inode, struct stat *statbuf)
{
	statbuf->st_dev = inode->i_dev;
	statbuf->st_ino = inode->i_ino;
	statbuf->st_mode = inode->i_mode;
	statbuf->st_nlink = inode->i_nlink;
	statbuf->st_uid = inode->i_uid;
	statbuf->st_gid = inode->i_gid;
	statbuf->st_rdev = inode->i_rdev;
	statbuf->st_size = inode->i_size;
	statbuf->st_atime = inode->i_atime;
	statbuf->st_mtime = inode->i_mtime;
	statbuf->st_ctime = inode->i_ctime;
}

long sys_stat(char *filename, struct stat *statbuf)
{
	struct inode *inode;

	if (!(inode = namei(filename, NULL)))
		return -ENOENT;

	copy_stat(inode, statbuf);
	iput(inode);

	return 0;
}

long sys_fstat(unsigned long fd, struct stat *statbuf)
{
	struct task *task = CURRENT_TASK();

	if (fd > NR_OPEN || !(task->file[fd]))
		return -EBADF;

	lock_inode(task->file[fd]->f_inode);
	copy_stat(task->file[fd]->f_inode, statbuf);
	unlock_inode(task->file[fd]->f_inode);

	return 0;
}

long sys_chown(char *filename, uid_t uid, gid_t gid)
{
	struct inode *inode;

	if ((CURRENT_TASK() )->uid != 0)
		return -EPERM;
	if (!(inode = namei(filename, NULL)))
		return -ENOENT;

	inode->i_uid = uid;
	inode->i_gid = gid;
	inode->i_flag |= I_DIRTY;
	iput(inode);
	return 0;
}

long sys_chmod(char *filename, mode_t mode)
{
	struct inode *inode;
	struct task *current;

	if (!(inode = namei(filename, NULL)))
		return -ENOENT;

	current = CURRENT_TASK();
	if (current->uid != inode->i_uid && current->uid != 0) {
		iput(inode);
		return -EACCESS;
	}

	inode->i_mode = (inode->i_mode & ~07777) | (mode & 07777);
	inode->i_flag |= I_DIRTY;
	iput(inode);
	return 0;
}

long sys_utime(char *filename, struct utimebuf *timebuf)
{
	struct inode *inode;

	if (!(inode = namei(filename, NULL)))
		return -ENOENT;

	if (timebuf) {
		inode->i_ctime = timebuf->ctime;
	}
	inode->i_atime = inode->i_mtime = current_time();
	inode->i_flag |= I_DIRTY;
	iput(inode);
	return 0;
}
