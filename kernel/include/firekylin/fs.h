/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _FS_H
#define _FS_H

#include <sys/types.h>
#include <sys/param.h>
#include <firekylin/lock.h>
#include <dirent.h>

struct buffer {
	dev_t           b_dev;
	unsigned int    b_block;
	unsigned short  b_flag;
	unsigned short  b_count;
	sleeplock_t     b_lock;
	char          * b_data;
	struct buffer * b_hash_prev;
	struct buffer * b_hash_next;
	struct buffer * b_free_prev;
	struct buffer * b_free_next;
};

/* Bits of buffer->b_flag */
#define B_VALID 	0x0002
#define B_DIRTY 	0x0004

#define lock_buffer(buf)	require_lock(&((buf)->b_lock))
#define unlock_buffer(buf)	release_lock(&((buf)->b_lock))

#define INODE_EXT_SIZE	32
struct inode {
	dev_t 		     i_dev;
	ino_t 		     i_ino;
	mode_t 		     i_mode;
	nlink_t 	     i_nlink;
	uid_t 		     i_uid;
	gid_t 		     i_gid;
	dev_t		     i_rdev;
	off_t 		     i_size;
	time_t 		     i_atime;
	time_t 		     i_mtime;
	time_t 		     i_ctime;
	unsigned short 	     i_flag;
	unsigned short 	     i_count;
	sleeplock_t	     i_lock;
	struct fs_operation *i_op;
	unsigned char        i_ext[INODE_EXT_SIZE];
};

/* Bits of inode->i_flag */
#define I_VALID		0x0002
#define I_DIRTY		0x0004
#define I_MOUNT		0x0008

#define lock_inode(inode)	require_lock(&((inode)->i_lock))
#define unlock_inode(inode)	release_lock(&((inode)->i_lock))

#define SUPER_EXT_SIZE	64
struct super {
	dev_t                s_dev;
	unsigned short       s_flag;
	unsigned short       s_count;
	sleeplock_t	     s_lock;
	struct fs_operation *s_op;
	struct inode        *s_imount;
	unsigned char        s_ext[SUPER_EXT_SIZE];
};

/* Bits of super->s_flag */
#define S_VALID		0x0002
#define S_DIRTY		0x0004
#define S_WRITEABLE	0x0008

#define lock_super(super)	require_lock(&((super)->s_lock))
#define unlock_super(super)	release_lock(&((super)->s_lock))

struct file {
	unsigned long  f_mode;
	unsigned long  f_count;
	unsigned long  f_pos;
	struct inode * f_inode;
	sleeplock_t    f_lock;
};

#define lock_file(file)		require_lock(&((file)->f_lock))
#define unlock_file(file)	release_lock(&((file)->f_lock))

struct fs_operation{
	/* super operation */
	int (*super_read)(struct super *super);
	int (*super_write)(struct super *super);

	/* inode operation */
	int (*inode_read)(struct inode *inode);
	int (*inode_write)(struct inode *inode);
	int (*lookup)(struct inode *inode, char *filename, struct inode **res);
	int (*mknod)(struct inode *inode, char *name,mode_t mode,dev_t dev);
	int (*mkdir)(struct inode *dir_inode,char *basename,mode_t mode);
	int (*link)(struct inode *dir_inode,char *name,struct inode *inode);
	int (*unlink)(struct inode *dir_inode,char *basename);
	int (*rmdir)(struct inode *dir_inode,char *basename);
	int (*rename)(struct inode *inode,char *old,char *new);

	/* file operation */
	int (*file_read)(struct file *file, char *buf, size_t size);
	int (*file_readdir)(struct file *file, char *buf, size_t size);
	int (*file_write)(struct file *file, char *buf, size_t size);
};

struct fs_type{
	char                *fst_name;
	struct fs_operation *fst_op;
};

extern struct buffer * bread(dev_t dev, long block);
extern void            brelse(struct buffer * buf);
extern struct super  * get_super(dev_t dev);
extern void            put_super(struct super *super);
extern struct inode  * iget(dev_t dev, ino_t ino);
extern struct inode  * idup(struct inode *inode);
extern void            iput(struct inode *inode);
extern struct inode  * namei(char *path, char **basename);

#define NR_FILE 	64
extern struct file file_table[NR_FILE];
extern sleeplock_t file_table_lock;

#endif
