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

int minix1_read_super(struct super *super)
{
	struct minix1_super *m1_super;
	struct buffer *buf;
	struct minix_s_ext *s_ext = (struct minix_s_ext*) super->s_ext;

	buf = bread(super->s_dev, 1);
	m1_super = (struct minix1_super *) (buf->b_data);
	if (m1_super->s_magic != 0x138f) {
		printk("Not minix file system %x", super->s_dev);
		brelse(buf);
		return -1;
	}

	s_ext->s_ninodes = m1_super->s_ninodes;
	s_ext->s_nzones = m1_super->s_nzones;
	s_ext->s_imap_blocks = m1_super->s_imap_blocks;
	s_ext->s_zmap_blocks = m1_super->s_zmap_blocks;
	s_ext->s_firstdatazone = m1_super->s_firstdatazone;
	s_ext->s_log_zone_size = m1_super->s_log_zone_size;
	s_ext->s_max_size = m1_super->s_max_size;
	s_ext->s_magic = m1_super->s_magic;

	brelse(buf);
	return 0;
}

int minix1_write_super(struct super *super)
{
	return 0;
}
