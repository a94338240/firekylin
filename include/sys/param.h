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

#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

/* clock interrupt one seconds */
#define HZ		100

/* Max file open one task */
#define NR_OPEN		32

/* Max task exsit */
#define NR_TASK		16

/* Max inode cache in memory */
#define NR_INODE	32

/* Max supper block in system */
#define NR_SUPER	4

/* Mac buffer cache in system */
#define NR_BUFFER	64

/* buffer cache size */
#define BUF_SIZE	1024

#endif
