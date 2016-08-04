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
