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

static void m1_read_inode(struct inode *inode, struct minix1_inode *m1)
{
	struct minix1_inode *i_ext = (struct minix1_inode*) inode->i_ext;

	inode->i_mode = m1->i_mode;
	inode->i_nlink = m1->i_nlinks;
	inode->i_uid = m1->i_uid;
	inode->i_gid = m1->i_gid;
	inode->i_size = m1->i_size;
	inode->i_atime = inode->i_mtime = inode->i_ctime = m1->i_time;
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		inode->i_rdev = m1->i_zone[0];
	else {
		i_ext->i_zone[0] = m1->i_zone[0];
		i_ext->i_zone[1] = m1->i_zone[1];
		i_ext->i_zone[2] = m1->i_zone[2];
		i_ext->i_zone[3] = m1->i_zone[3];
		i_ext->i_zone[4] = m1->i_zone[4];
		i_ext->i_zone[5] = m1->i_zone[5];
		i_ext->i_zone[6] = m1->i_zone[6];
		i_ext->i_zone[7] = m1->i_zone[7];
		i_ext->i_zone[8] = m1->i_zone[8];
	}
	inode->i_flag |= I_VALID;
}

static void m1_write_inode(struct inode *inode, struct minix1_inode *m1)
{
	struct minix1_inode *i_ext = (struct minix1_inode*) inode->i_ext;

	m1->i_mode = inode->i_mode;
	m1->i_uid = inode->i_uid;
	m1->i_gid = inode->i_gid;
	m1->i_nlinks = inode->i_nlink;
	m1->i_size = inode->i_size;
	m1->i_time = inode->i_ctime;
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		m1->i_zone[0] = inode->i_rdev;
	else {
		m1->i_zone[0] = i_ext->i_zone[0];
		m1->i_zone[1] = i_ext->i_zone[1];
		m1->i_zone[2] = i_ext->i_zone[2];
		m1->i_zone[3] = i_ext->i_zone[3];
		m1->i_zone[4] = i_ext->i_zone[4];
		m1->i_zone[5] = i_ext->i_zone[5];
		m1->i_zone[6] = i_ext->i_zone[6];
		m1->i_zone[7] = i_ext->i_zone[7];
		m1->i_zone[8] = i_ext->i_zone[8];
	}
	inode->i_flag &= ~I_DIRTY;
}

static int __minix1_rw_inode(struct inode *inode, int rw)
{
	struct buffer *buf;
	struct minix1_inode *m1;
	long block;

	struct super *super = get_super(inode->i_dev);
	struct minix_s_ext *s_ext = (struct minix_s_ext*) super->s_ext;

	block = 2 + s_ext->s_imap_blocks + s_ext->s_zmap_blocks
			+ (inode->i_ino - 1) / INODES_PER_BLOCK;
	put_super(super);

	buf = bread(inode->i_dev, block);
	m1 = (struct minix1_inode *) buf->b_data
			+ (inode->i_ino - 1) % INODES_PER_BLOCK;
	if (rw) {
		m1_read_inode(inode, m1);
	} else {
		m1_write_inode(inode, m1);
		buf->b_flag |= B_DIRTY;
	}
	brelse(buf);
	return 0;
}

int minix1_read_inode(struct inode * inode)
{
	return __minix1_rw_inode(inode, 1);
}

int minix1_write_inode(struct inode * inode)
{
	return __minix1_rw_inode(inode, 0);
}

static int __minix1_bmap(struct inode *inode, int block, int create)
{
	struct buffer *buffer;
	int res;
	struct minix1_inode *i_ext = (struct minix1_inode*) inode->i_ext;

	if (block < 7) {
		if (create && (!i_ext->i_zone[block])) {
			i_ext->i_zone[block] = minix1_alloc_block(inode->i_dev);
			inode->i_ctime = current_time();
			inode->i_flag |= I_DIRTY;
		}
		return i_ext->i_zone[block];
	}

	block -= 7;
	if (block < 512) {
		if (create && !i_ext->i_zone[7]) {
			i_ext->i_zone[7] = minix1_alloc_block(inode->i_dev);
			inode->i_ctime = current_time();
			inode->i_flag |= I_DIRTY;
		}
		if (!i_ext->i_zone[7])
			return 0;
		buffer = bread(inode->i_dev, i_ext->i_zone[7]);
		res = *((short*) (buffer->b_data + block * 2));
		if (create && !res) {
			res = minix1_alloc_block(inode->i_dev);
			*((short*) (buffer->b_data + block * 2)) = res;
			buffer->b_flag |= B_DIRTY;
		}
		brelse(buffer);
		return res;
	}
	return 0;
}

int minix1_rbmap(struct inode *inode, int block)
{
	return __minix1_bmap(inode, block, 0);
}

int minix1_wbmap(struct inode *inode, int block)
{
	return __minix1_bmap(inode, block, 1);
}
