/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/errno.h>
#include <kernel.h>
#include <sched.h>
#include <driver.h>
#include <fs.h>

struct file file_table[NR_FILE];
sleeplock_t file_table_lock;

long char_open(dev_t dev)
{
	int major = MAJOR(dev);

	if (major > DEV_CHAR_MAX || !char_table[major]) {
		printk("dev not exist:%x", dev);
		return -ENODEV;
	}
	if (char_table[major]->open)
		return char_table[major]->open(dev);
	return 0;
}

long blk_open(dev_t dev)
{
	int major = MAJOR(dev);

	if (major > DEV_BLK_MAX || !blk_table[major]) {
		printk("dev not exist:%x", dev);
		return -ENODEV;
	}
	if (blk_table[major]->open)
		return blk_table[major]->open(dev);
	return 0;
}

long sys_access(char *filename, long mode)
{
	struct inode *inode;
	mode_t tmp_mode = 0;
	struct task *current;

	if (!(inode = namei(filename, NULL)))
		return -EACCESS;
	if (mode == F_OK) {
		iput(inode);
		return 0;
	}

	mode &= 7;
	current = CURRENT_TASK();
	if (current->uid == inode->i_uid)
		tmp_mode |= (mode) << 6;
	if (current->gid == inode->i_gid)
		tmp_mode |= (mode) << 3;
	tmp_mode |= (mode);

	if (tmp_mode & inode->i_mode) {
		iput(inode);
		return 0;
	}

	iput(inode);
	return -EACCESS;
}

long sys_open(char *path, long flag, mode_t mode)
{
	extern long sys_mknod(char *filename, mode_t mode, dev_t dev);
	int fd;
	struct file *file;
	struct inode *inode;
	struct task *current = CURRENT_TASK();

	for (fd = 0; fd < NR_OPEN; fd++) {
		if (!current->file[fd])
			break;
	}
	if (fd >= NR_OPEN)
		return -EINVAL;

	for (file = file_table; file < file_table + NR_FILE; file++)
		if (!file->f_count)
			break;
	if (file >= file_table + NR_FILE)
		return -EINVAL;

	if (!(inode = namei(path, NULL))) {
		if (!(flag & O_CREAT)) {
			return -ENOENT;
		}
		if (sys_mknod(path, S_IFREG | (mode & 07777), 0) < 0)
			return -EAGAIN;
		inode = namei(path, NULL);
	}
	unlock_inode(inode);
	file->f_count = 1;
	file->f_inode = inode;
	file->f_pos = 0;
	file->f_mode = flag;
	current->file[fd] = file;

	return fd;
}

long sys_chdir(char *path)
{
	struct inode *inode;
	struct task *current = CURRENT_TASK();

	if (!(inode = namei(path, NULL)))
		return -ENOENT;

	if (!(S_ISDIR(inode->i_mode))) {
		iput(inode);
		return -ENOTDIR;
	}

	if (inode != current->pwd) {
		iput(current->pwd);
		current->pwd = inode;
		unlock_inode(inode);
	} else{
		iput(inode);
	}

	return 0;
}

long sys_fchdir(unsigned long fd)
{
	struct inode *inode;
	struct file *file;
	struct task *current = CURRENT_TASK();

	if (fd > NR_OPEN || !(file = current->file[fd]))
		return -EBADF;

	inode = idup(file->f_inode);
	if (!S_ISDIR(inode->i_mode)) {
		iput(inode);
		return -ENOTDIR;
	}

	if (inode != current->pwd) {
		iput(current->pwd);
		current->pwd = inode;
		unlock_inode(inode);
	} else{
		iput(inode);
	}
	return 0;
}
