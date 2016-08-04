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

#include "minix.h"

static struct buffer * find_entry(struct inode *dir_inode, char *filename,
		struct minix1_dirent **res_de)
{
	struct buffer *buf;
	struct minix1_dirent *de;

	for (int i = 0; i < 7 + 512; i++) {
		buf = bread(dir_inode->i_dev, minix1_rbmap(dir_inode, i));
		if (!buf)
			panic("add_entry:can not read buf");

		de = (struct minix1_dirent *) buf->b_data;
		for (int j = 0; j < 1024 / sizeof(struct minix1_dirent); j++) {
			if (i * 1024 + j * sizeof(struct minix1_dirent)
					> dir_inode->i_size) {
				brelse(buf);
				*res_de = NULL;
				return NULL;
			}

			if (!strncmp(de->name, filename, MINIX_NAME_LEN)) {
				*res_de = de;
				return buf;
			}
			de++;
		}
		brelse(buf);
	}
	*res_de = NULL;
	return NULL;
}

static int add_entry(struct inode *inode, char *name, ino_t ino)
{
	struct buffer *buf;
	struct minix1_dirent *de;
	int size = 0;

	if (!inode)
		panic("find_entry:inode is NULL");

	for (int i = 0; i < 7 + 512; i++) {
		buf = bread(inode->i_dev, minix1_wbmap(inode, i));
		if (!buf)
			panic("add_entry:can not read buf");

		de = (struct minix1_dirent *) buf->b_data;
		for (int j = 0; j < 1024 / sizeof(struct minix1_dirent); j++) {
			if (size < inode->i_size && de->ino) {
				size += sizeof(struct minix1_dirent);
				de++;
				continue;
			}

			strncpy(de->name, name, MINIX_NAME_LEN);
			de->ino = ino;
			buf->b_flag |= B_DIRTY;

			size += sizeof(struct minix1_dirent);

			if (size > inode->i_size) {
				inode->i_size = size;
				inode->i_flag |= I_DIRTY;
			}
			brelse(buf);
			return 0;
		}
		brelse(buf);
		return 1;
	}
	return 1;
}

int count_entry(struct inode *inode)
{
	struct buffer *buf;
	struct minix1_dirent *de;
	int count = 0;

	for (int i = 0; i < 7 + 512; i++) {
		buf = bread(inode->i_dev, minix1_rbmap(inode, i));
		if (!buf)
			panic("add_entry:can not read buf");

		de = (struct minix1_dirent *) buf->b_data;
		for (int j = 0; j < 1024 / sizeof(struct minix1_dirent); j++) {

			if (i * 1024 + j * sizeof(struct minix1_dirent)
					> inode->i_size) {

				brelse(buf);
				return count;
			}

			if (!de->ino) {
				de++;
				continue;
			}
			count++;
			de++;
		}
		brelse(buf);
	}
	return count;
}

int minix1_lookup(struct inode *dir_inode, char *filename,
		struct inode **res_inode)
{
	struct buffer *buf;
	struct inode *inode;
	struct minix1_dirent *de;

	if (filename[0] == '.' && filename[1] == 0) {
		*res_inode = dir_inode;
		return 0;
	}

	buf = find_entry(dir_inode, filename, &de);

	if (!buf) {
		iput(dir_inode);
		*res_inode = NULL;
		return 1;
	}

	if (de->ino == dir_inode->i_ino) {
		brelse(buf);
		*res_inode = dir_inode;
		return 0;
	}

	inode = iget(dir_inode->i_dev, de->ino);
	if (!inode) {
		brelse(buf);
		*res_inode = NULL;
		return 1;
	}
	brelse(buf);
	iput(dir_inode);
	*res_inode = inode;
	return 0;
}

int minix1_mknod(struct inode *dir_inode, char *name, mode_t mode, dev_t dev)
{
	struct buffer *buf;
	struct minix1_dirent *de;
	struct inode *new_inode;

	if ((buf = find_entry(dir_inode, name, &de))) {
		brelse(buf);
		return -EEXIST;
	}

	if (!(new_inode = minix1_alloc_inode(dir_inode->i_dev))) {
		return -EAGAIN;
	}
	new_inode->i_mode = mode;
	if (S_ISCHR(mode) || S_ISBLK(mode))
		new_inode->i_rdev = dev;

	if ((add_entry(dir_inode, name, new_inode->i_ino))) {
		iput(new_inode);
		minix1_free_inode(dir_inode->i_dev, new_inode->i_ino);
		return -1;
	}
	new_inode->i_flag |= I_DIRTY;
	iput(new_inode);
	return 0;
}

int minix1_mkdir(struct inode *dir_inode, char *name, mode_t mode)
{
	struct buffer *buf;
	struct minix1_dirent *de;
	struct inode *inode;

	if ((buf = find_entry(dir_inode, name, &de))) {
		brelse(buf);
		return -EEXIST;
	}

	if (!(inode = minix1_alloc_inode(dir_inode->i_dev)))
		return -EAGAIN;
	inode->i_mode = mode;
	inode->i_flag |= I_DIRTY;

	add_entry(dir_inode, name, inode->i_ino);
	minix1_link(inode, ".", inode);
	minix1_link(inode, "..", dir_inode);
	iput(inode);
	return 0;
}

int minix1_link(struct inode *dir_inode, char *name, struct inode *inode)
{
	struct buffer *buf;
	struct minix1_dirent *de;

	if ((buf = find_entry(dir_inode, name, &de))) {
		brelse(buf);
		return -EEXIST;
	}

	inode->i_nlink++;
	inode->i_flag |= I_DIRTY;
	return add_entry(dir_inode, name, inode->i_ino);
}

int minix1_unlink(struct inode *dir_inode, char *name)
{
	struct minix1_dirent *de;
	struct buffer *buf;
	struct inode *del_inode;

	buf = find_entry(dir_inode, name, &de);
	if (!buf)
		return -ENOENT;

	del_inode = iget(dir_inode->i_dev, de->ino);

	if (!del_inode) {
		brelse(buf);
		return -EAGAIN;
	}
	if (del_inode->i_count != 1) {
		iput(del_inode);
		brelse(buf);
		return -EBUSY;
	}
	if (S_ISDIR(del_inode->i_mode)) {
		iput(del_inode);
		brelse(buf);
		return -EISDIR;
	}

	del_inode->i_nlink--;
	del_inode->i_flag |= I_DIRTY;
	iput(del_inode);
	de->ino = 0;
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}

int minix1_rmdir(struct inode *dir_inode, char *name)
{
	struct minix1_dirent *de;
	struct buffer *buf;
	struct inode *del_inode;

	buf = find_entry(dir_inode, name, &de);
	if (!buf)
		return -ENOENT;

	del_inode = iget(dir_inode->i_dev, de->ino);

	if (!del_inode) {
		brelse(buf);
		return -EAGAIN;
	}
	if (del_inode->i_count != 1) {
		iput(del_inode);
		brelse(buf);
		return -EBUSY;
	}
	if (!S_ISDIR(del_inode->i_mode)) {
		iput(del_inode);
		brelse(buf);
		return -ENOTDIR;
	}

	minix1_unlink(del_inode, ".");
	minix1_unlink(del_inode, "..");
	brelse(buf);
	iput(del_inode);
	minix1_unlink(dir_inode, name);
	return 0;
}

int minix1_rename(struct inode *inode, char *old, char *new)
{
	struct minix1_dirent *de;
	struct buffer *buf;

	buf = find_entry(inode, old, &de);
	if (!buf)
		return -ENOENT;
	strncpy(de->name, new, MINIX_NAME_LEN);
	buf->b_flag |= B_DIRTY;
	brelse(buf);
	return 0;
}
