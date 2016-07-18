/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "minix.h"

int minix1_free_block(dev_t dev, int block)
{
	struct buffer * buf;
	struct super *super = get_super(dev);
	struct minix_s_ext *s_ext = (struct minix_s_ext*) super->s_ext;

	if (block < s_ext->s_firstdatazone || block > s_ext->s_nzones)
		panic("block too big %x", block);
	buf = bread(dev, block);
	if (buf->b_count != 1)
		panic("block is using");
	brelse(buf);
	buf = bread(dev, 2 + s_ext->s_imap_blocks + block / (8 * 1024));
	clr_bit(buf->b_data, block % (8 * 1024));
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}

int minix1_free_inode(dev_t dev, ino_t ino)
{
	struct buffer * buf;
	struct super *super = get_super(dev);
	struct minix_s_ext *s_ext = (struct minix_s_ext*) super->s_ext;

	if (ino < 1 || ino > s_ext->s_ninodes)
		panic("block too big %x", ino);

	buf = bread(dev, 2 + ino / (8 * 1024));
	clr_bit(buf->b_data, ino % (8 * 1024));
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}

int minix1_alloc_block(dev_t dev)
{
	int res, tmp;
	struct buffer *bh;
	struct super *super = get_super(dev);
	struct minix_s_ext *s_ext = (struct minix_s_ext*) super->s_ext;

	for (int i = 0; i < s_ext->s_zmap_blocks; i++) {
		bh = bread(dev, 2 + s_ext->s_imap_blocks + i);
		if (!bh)
			panic("alloc_inode: cann't inode block");

		tmp = find_bit(bh->b_data, 1024);

		res = i * 1024 * 8 + tmp;
		if (tmp > s_ext->s_nzones) {
			brelse(bh);
			put_super(super);
			return 0;
		}
		set_bit(bh->b_data, tmp);
		bh->b_flag |= B_DIRTY;
		brelse(bh);
		res += s_ext->s_firstdatazone;
		put_super(super);
		return res;
	}
	put_super(super);
	return 0;
}

struct inode * minix1_alloc_inode(dev_t dev)
{
	struct buffer *bh;
	struct inode *inode;
	struct task *current;
	struct fs_operation *fs_op;
	ino_t res;
	int tmp;
	struct super * super = get_super(dev);
	struct minix_s_ext *s_ext = (struct minix_s_ext*) super->s_ext;

	for (int i = 0; i < s_ext->s_imap_blocks; i++) {
		bh = bread(dev, 2 + i);
		if (!bh)
			panic("alloc_inode: cann't inode block");

		tmp = find_bit(bh->b_data, 1024);

		res = i * 1024 * 8 + tmp;
		if (tmp > s_ext->s_ninodes) {
			brelse(bh);
			put_super(super);
			return NULL;
		}

		set_bit(bh->b_data, tmp);
		bh->b_flag |= B_DIRTY;
		brelse(bh);
		fs_op = super->s_op;
		put_super(super);

		inode = iget(dev, res);
		if (!inode) {
			minix1_free_inode(dev, res);
			return NULL;
		}

		current = CURRENT_TASK();
		inode->i_nlink = 1;
		inode->i_uid = current->uid;
		inode->i_gid = current->gid;
		inode->i_size = 0;
		inode->i_atime = inode->i_mtime = inode->i_ctime =
				current_time();
		inode->i_op = fs_op;
		return inode;
	}
	put_super(super);
	return NULL;
}
