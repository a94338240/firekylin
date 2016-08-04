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

#ifndef _ERRNO_H
#define _ERRNO_H

#define ERROR		1
#define EPERM		2
#define ENOENT		3
#define EINTR		4
#define EIO		5
#define E2BIG		6
#define EISDIR		7
#define EINVAL		8
#define EACCESS		9
#define EBADF		10
#define ENOTDIR		11
#define ENOMEM		12
#define EAGAIN		13
#define ENOEXEC		14
#define ENODEV		15
#define EMFILE		16
#define EEXIST		17
#define ENOSPACE	18
#define ERSCH		19
#define EBUSY		20
#define ESPIPE		21
#define ENOTBLK		22

extern int errno;

#endif
