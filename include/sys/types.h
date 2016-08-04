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

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#ifndef NULL
#define NULL 		((void*)0)
#endif

typedef unsigned long 	size_t;
typedef signed   long 	ssize_t;

typedef unsigned long 	time_t;
typedef unsigned long 	clock_t;

typedef signed int 	uid_t;
typedef signed int 	gid_t;
typedef signed int 	pid_t;

typedef unsigned int 	dev_t;
typedef unsigned int 	ino_t;
typedef unsigned int 	mode_t;
typedef unsigned int 	nlink_t;

typedef unsigned long 	off_t;

#endif
