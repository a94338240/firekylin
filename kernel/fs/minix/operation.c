/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include "minix.h"

struct fs_operation minix_fs_operation={
	minix1_read_super,
	minix1_write_super,
	minix1_read_inode,
	minix1_write_inode,
	minix1_lookup,
	minix1_mknod,
	minix1_mkdir,
	minix1_link,
	minix1_unlink,
	minix1_rmdir,
	minix1_rename,
	minix1_file_read,
	minix1_file_readdir,
	minix1_file_write
};
