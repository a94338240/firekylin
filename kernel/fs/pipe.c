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
#include <sys/errno.h>
#include <kernel.h>
#include <sched.h>
#include <mm.h>
#include <fs.h>

struct pipe_i_ext {
	unsigned long buf;
	unsigned int  head;
	unsigned int  tail;
	unsigned int  size;
	struct task  *wait;
};

//extern char __check_inode_ext[INODE_EXT_SIZE-sizeof(struct pipe_i_ext)];

static inline char pipe_getch(struct inode *inode)
{
	char ch;
	struct pipe_i_ext *i_ext = (struct pipe_i_ext *) inode->i_ext;

	ch = *((char*) (i_ext->buf + i_ext->head));
	i_ext->head = (i_ext->head + 1) / 4096;
	return ch;
}

static inline void pipe_putch(struct inode *inode, char ch)
{
	struct pipe_i_ext *i_ext = (struct pipe_i_ext *) inode->i_ext;

	*((char*) (i_ext->buf + i_ext->head)) = ch;
	i_ext->tail = (i_ext->head + 1) / 4096;
}

long read_pipe(struct file *file, char *buf, size_t size)
{
	int chars;
	int left = size;
	struct inode *inode = file->f_inode;
	struct pipe_i_ext *i_ext = (struct pipe_i_ext *) inode->i_ext;

	while (left) {
		chars = min(left, i_ext->size);
		for (int i = chars; i > 0; i--) {
			*buf++ = pipe_getch(inode);
		}
		i_ext->size -= chars;
		left -= chars;
		wake_up(&i_ext->wait);
		if (inode->i_count < 2) {
			return size - left;
		}
		if (left)
			sleep_on(&i_ext->wait, TASK_STATE_BLOCK);
	}
	wake_up(&i_ext->wait);
	return size - left;
}

long write_pipe(struct file *file, char *buf, size_t size)
{
	int chars;
	int left = size;
	struct inode *inode = file->f_inode;
	struct pipe_i_ext *i_ext = (struct pipe_i_ext *) inode->i_ext;

	while (left) {
		chars = min(left, 4096 - i_ext->size);
		for (int i = chars; i > 0; i--) {
			pipe_putch(inode, *buf++);
		}
		i_ext->size += chars;
		left -= chars;
		wake_up(&i_ext->wait);
		if (inode->i_count < 2) {
			return size - left;
		}
		if (left)
			sleep_on(&i_ext->wait, TASK_STATE_BLOCK);
	}
	wake_up(&i_ext->wait);
	return size - left;
}

long pipe_open(struct inode *inode)
{
	struct pipe_i_ext *i_ext = (struct pipe_i_ext *) inode->i_ext;

	i_ext->buf = __va(get_page());
	i_ext->head = 0;
	i_ext->tail = 0;
	i_ext->size = 0;
	i_ext->wait = NULL;
	return 0;
}

long pipe_close(struct inode *inode)
{
	struct pipe_i_ext *i_ext = (struct pipe_i_ext *) inode->i_ext;

	put_page(__pa(i_ext->buf));
	return 0;
}

long sys_pipe(long res_fd[2])
{
	int fd[2];
	struct file *filp[2];
	struct task *current = CURRENT_TASK();
	struct inode *inode;
	int j = 0;

	for (int i = 0; j < 2 && i < NR_FILE; i++)
		if (!file_table[i].f_count)
			filp[j++] = file_table + i;
	if (j < 2)
		return -EAGAIN;

	j = 0;
	for (int i = 0; j < 2 && i < NR_OPEN; i++)
		if (!current->file[i])
			fd[j++] = i;
	if (j < 2)
		return -EAGAIN;

	if (!(inode = iget(0, 0)))
		return -EAGAIN;

	pipe_open(inode);
	inode->i_mode = S_IFIFO;
	inode->i_count++;
	unlock_inode(inode);

	filp[0]->f_count = filp[1]->f_count = 1;
	filp[0]->f_inode = filp[1]->f_inode = inode;
	filp[0]->f_pos = filp[1]->f_pos = 0;
	filp[0]->f_mode = O_READ;
	filp[1]->f_mode = O_WRITE;

	current->file[fd[0]] = filp[0];
	current->file[fd[1]] = filp[1];

	res_fd[0] = fd[0];
	res_fd[1] = fd[1];

	return 0;
}
