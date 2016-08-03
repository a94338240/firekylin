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
#include <firekylin/kernel.h>
#include <firekylin/driver.h>
#include <firekylin/fs.h>
#include <errno.h>

static long write_char(struct file *file, char *buf, size_t size)
{
	dev_t dev = file->f_inode->i_rdev;
	int major = MAJOR(dev);
	if (major > DEV_CHAR_MAX || !char_table[major])
		panic("dev %x not exsit", dev);

	return char_table[major]->write(dev, buf, file->f_pos, size);
}

static long write_blk(struct file *file, char *buf, size_t size)
{
	struct buffer *bh;
	int chars, left;

	dev_t dev = file->f_inode->i_rdev;
	off_t off = file->f_pos;

	left = size;
	while (left) {
		bh = bread(dev, off / 1024);
		if (!bh)
			return -EIO;
		chars = min(left, 1024 - off % 1024);
		memcpy(bh->b_data + off % 1024, buf, chars);
		bh->b_flag |= B_DIRTY;
		brelse(bh);
		buf += chars;
		off += chars;
		left -= chars;
	}
	return size - left;
}

extern long write_pipe(struct file *file, char *buf, size_t size);

long sys_write(unsigned long fd, char *buf, size_t size)
{
	struct file *file;
	long res;

	if (fd > NR_OPEN || !(file = (CURRENT_TASK() )->file[fd]))
		return -EBADF;
	if (!(file->f_mode & O_WRITE))
		return -EBADF;

	lock_file(file);
	//lock_inode(file->f_inode);

	if (file->f_mode & O_APPEND)
		file->f_pos = file->f_inode->i_size;
	switch (file->f_inode->i_mode & S_IFMT) {
	case S_IFREG:
		res = file->f_inode->i_op->file_write(file, buf, size);
		break;
	case S_IFDIR:
		res = -EISDIR;
		break;
	case S_IFCHR:
		res = write_char(file, buf, size);
		break;
	case S_IFBLK:
		res = write_blk(file, buf, size);
		break;
	case S_IFIFO:
		res = write_pipe(file, buf, size);
		break;
	default:
		res = -EIO;
	}

	if (res > 0)
		file->f_pos += res;

	if ((S_ISREG(file->f_inode->i_mode) || S_ISDIR(file->f_inode->i_mode))
			&& file->f_pos > file->f_inode->i_size) {
		file->f_inode->i_size = file->f_pos;
		file->f_inode->i_ctime = current_time();
		file->f_inode->i_flag |= I_DIRTY;
	}

	//unlock_inode(file->f_inode);
	unlock_file(file);

	return res;
}
