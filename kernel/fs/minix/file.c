/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "minix.h"

int minix1_file_read(struct file *file, char * buf, size_t size)
{
	struct buffer *bh;
	int chars, left;

	struct inode *inode = file->f_inode;
	off_t off = file->f_pos;

	if (off >= inode->i_size)
		return 0;
	if (off + size >= inode->i_size)
		size = inode->i_size - off;

	left = size;
	while (left > 0) {
		bh = bread(inode->i_dev, minix1_rbmap(inode, off / 1024));
		if (!bh) {
			panic("read file error");
		}
		chars = min(left, 1024 - off % 1024);
		memcpy(buf, bh->b_data + off % 1024, chars);
		brelse(bh);
		buf += chars;
		off += chars;
		left -= chars;
	}
	return size - left;
}

int minix1_file_readdir(struct file *file, char * buf, size_t size)
{
	struct buffer *bh;
	struct minix1_dirent *minix1_dirent;
	struct dirent *dirent = (struct dirent *) buf;

	struct inode *inode = file->f_inode;
	off_t off = file->f_pos;

	if (off >= inode->i_size)
		return 0;

	bh = bread(inode->i_dev, minix1_rbmap(inode, off / 1024));
	if (!bh) {
		panic("read file error");
	}
	minix1_dirent = (struct minix1_dirent *) (bh->b_data + off % 1024);

	dirent->d_ino = minix1_dirent->ino;
	dirent->d_reclen = MINIX_NAME_LEN;
	strncpy(dirent->d_name, minix1_dirent->name, MINIX_NAME_LEN);

	brelse(bh);
	return sizeof(struct minix1_dirent);
}

int minix1_file_write(struct file *file, char * buf, size_t size)
{
	struct buffer *bh;
	int left, chars;

	struct inode *inode = file->f_inode;
	off_t off = file->f_pos;
	left = size;

	while (left) {
		bh = bread(inode->i_dev, minix1_wbmap(inode, off / 1024));
		if (!bh) {
			panic("write file error");
		}
		chars = min((1024 - off % 1024), left);
		memcpy(bh->b_data + off % 1024, buf, chars);
		off += chars;
		left -= chars;
		bh->b_flag |= B_DIRTY;
		brelse(bh);
	}
	return size - left;
}

int minix1_file_truncate(struct inode *inode)
{
//	struct buffer *buf;
//	unsigned short *p;
//
//	if(!(S_ISREG(inode->i_mode)|| S_ISDIR(inode->i_mode)))
//		return 0;
//	for(int i=0;i<7;i++){
//		if(inode->i_zone[i]){
//			minix1_free_block(inode->i_dev,inode->i_zone[i]);
//			inode->i_zone[i]=0;
//		}
//	}
//
//	if(inode->i_zone[7]){
//		buf=bread(inode->i_dev,inode->i_zone[7]);
//		p=(unsigned short *)buf->b_data;
//		for(int i=0;i<512;i++,p++){
//			if(*p){
//				minix1_free_block(inode->i_dev,*p);
//			}
//		}
//		brelse(buf);
//		minix1_free_block(inode->i_dev,inode->i_zone[7]);
//		inode->i_zone[7]=0;
//	}
//	inode->i_size=0;
//	inode->i_mtime=inode->i_ctime=current_time();
//	inode->i_flag|=I_DIRTY;
	return 0;
}
