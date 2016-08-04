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

#ifndef _MINIX_H
#define _MINIX_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <firekylin/kernel.h>
#include <firekylin/fs.h>
#include <arch/ia32/bits.h>
#include <errno.h>

struct minix1_inode {
	unsigned short i_mode;
	unsigned short i_uid;
	unsigned long  i_size;
	unsigned long  i_time;
	unsigned char  i_gid;
	unsigned char  i_nlinks;
	unsigned short i_zone[9];
};

struct minix1_super {
	unsigned short s_ninodes;
	unsigned short s_nzones;
	unsigned short s_imap_blocks;
	unsigned short s_zmap_blocks;
	unsigned short s_firstdatazone;
	unsigned short s_log_zone_size;
	unsigned long  s_max_size;
	unsigned short s_magic;
};

#define MINIX_NAME_LEN	30
struct minix1_dirent {
	unsigned short ino;
	char name[MINIX_NAME_LEN];
};

struct minix_i_ext{
	unsigned short i_zone[9];
};

struct minix_s_ext{
	unsigned short s_ninodes;
	unsigned short s_nzones;
	unsigned short s_imap_blocks;
	unsigned short s_zmap_blocks;
	unsigned short s_firstdatazone;
	unsigned short s_log_zone_size;
	unsigned long  s_max_size;
	unsigned short s_magic;
};

#define INODES_PER_BLOCK	(1024/sizeof(struct minix1_inode))

extern char __check_inode_ext[INODE_EXT_SIZE-sizeof(struct minix_i_ext)];
extern char __check_super_ext[SUPER_EXT_SIZE-sizeof(struct minix_s_ext)];

extern int minix1_read_super(struct super *super);
extern int minix1_write_super(struct super *super);
extern int minix1_read_inode(struct inode * inode);
extern int minix1_write_inode(struct inode * inode);
extern int minix1_lookup(struct inode *dir_inode, char *filename,
		struct inode **res_inode);
extern int minix1_alloc_block(dev_t dev);
extern int minix1_free_block(dev_t dev, int block);
extern struct inode * minix1_alloc_inode(dev_t dev);
extern int minix1_free_inode(dev_t dev, ino_t ino);
extern int minix1_rbmap(struct inode *inode, int block);
extern int minix1_wbmap(struct inode *inode, int block);
extern int minix1_mknod(struct inode *dir_inode, char *name, mode_t mode,
		dev_t dev);
extern int minix1_mkdir(struct inode *dir_inode,char *name,mode_t mode);
extern int minix1_link(struct inode *dir_inode,char *name, struct inode *inode);
extern int minix1_unlink(struct inode *dir_inode, char *name);
extern int minix1_rmdir(struct inode *dir_inode, char *name);
extern int minix1_rename(struct inode *inode, char *old, char *new);
extern int minix1_file_read(struct file *file, char * buf, size_t size);
extern int minix1_file_readdir(struct file *file, char * buf, size_t size);
extern int minix1_file_write(struct file *file, char * buf, size_t size);

#endif
