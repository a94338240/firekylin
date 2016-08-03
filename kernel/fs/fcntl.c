/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <errno.h>

static long dupfd(long fd, unsigned long arg)
{
	extern long sys_close(long fd);
	struct task *current;

	if (arg > NR_OPEN)
		return -EBADF;

	if (arg)
		sys_close(arg);
	current = CURRENT_TASK();
	while (arg < NR_OPEN) {
		if (current->file[arg]) {
			arg++;
			continue;
		}
		current->file[arg] = current->file[fd];
		current->file[fd]->f_count++;
		return arg;
	}
	return -EMFILE;
}

long sys_lseek(long fd, long off, int where)
{
	struct file *file;
	if (fd > NR_OPEN || !(file = (CURRENT_TASK() )->file[fd]))
		return -EBADF;
	switch (where) {
	case SEEK_SET:
		if (off < 0)
			return -EINVAL;
		file->f_pos = off;
		break;
	case SEEK_CUR:
		if (file->f_pos + off < 0)
			return -EINVAL;
		file->f_pos += off;
		break;
	case SEEK_END:
		if (file->f_inode->i_size + off < 0)
			return -EINVAL;
		file->f_pos = file->f_inode->i_size + off;
		break;
	default:
		return -EINVAL;
	}
	return file->f_pos;
}

long sys_fcntl(unsigned long fd, long cmd, long arg)
{
	struct file *file;

	if (fd > NR_OPEN || !(file = (CURRENT_TASK() )->file[fd]))
		return -EBADF;

	switch (cmd) {
	case F_DUPFD:
		return dupfd(fd, arg);
	default:
		return -EIO;
	}
}
