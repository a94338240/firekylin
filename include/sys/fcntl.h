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

#ifndef _SYS_FCNTL_H
#define _SYS_FCNTL_H

#include <sys/types.h>

/* Bits of open flag */
#define	O_READ		0x0001	/* Read flag.				*/
#define O_WRITE		0x0002	/* Write flag.				*/
#define O_RDWR		0x0003	/* O_READ | O_WRITE			*/
#define	O_APPEND	0x0004	/* Set append mode.			*/
#define O_CREAT		0x0100	/* Create file if it does not exist.	*/
#define O_TRUNC		0x0200	/* Truncate flag.			*/
#define O_EXCL		0x0400	/* Exclusive use flag.			*/
#define O_NOCTTY	0x0800	/* Do not assign controlling terminal.	*/

/* Values of fcntl cmd */
#define F_DUPFD		0	/* duplicate file descriptor                */
#define F_GETFD		1	/* get file descriptor flags                */
#define F_SETFD		2	/* set file descriptor flags                */
#define F_GETFL		3	/* get file status flags                    */
#define F_SETFL		4	/* set file status flags                    */
#define F_GETLK		5	/* get record locking information           */
#define F_SETLK 	6	/* set record locking information           */
#define F_SETLKW	7	/* set record locking info; wait if blocked */
#define F_FREESP	8	/* free a section of a regular file         */

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

/* Struct of file lock */
struct flock {
	short l_type; 		/* type: F_RDLCK, F_WRLCK, or F_UNLCK 	*/
	short l_whence; 	/* flag for starting offset   		*/
	off_t l_start; 		/* relative offset in bytes 		*/
	off_t l_len; 		/* size; if 0, then until EOF 		*/
	pid_t l_pid; 		/* process id of the locks' owner 	*/
};

extern int open(const char *path, int flag, ...);
extern int fcntl(int fd, int cmd, ...);

#endif
