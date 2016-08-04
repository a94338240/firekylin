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

#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H

#include <sys/types.h>

/* Values used by access() */
#define F_OK		0	/* test file is exist      */
#define X_OK		1	/* test file is executable */
#define W_OK		2	/* test file is writable   */
#define R_OK		4	/* test file is readable   */

/* standard I/O fileno */
#define STDIN_FILENO	0	/* file descriptor of stdin  */
#define STDOUT_FILENO	1	/* file descriptor of stdout */
#define STDERR_FILENO	2	/* file descriptor of stderr */

#define PIPE_READ_ID	0
#define PIPE_WRITE_ID	1

extern char **environ;

extern pid_t fork();
extern pid_t getpid();
extern pid_t setgrp();
extern pid_t setsid();
extern uid_t getuid();
extern gid_t getgid();
extern uid_t setuid(uid_t uid);
extern gid_t setgid(gid_t gid);
extern ssize_t read(int fd, void * buf, size_t size);
extern ssize_t write(int fd, void * buf, size_t size);
extern int execl(const char *path, const char *arg0, ...);
extern int execv(const char *path, char **argv);
extern int execle(const char *path, const char *arg0, ...);
extern int execve(const char *path, char **argv, char **envp);
extern int execlp(const char *file, const char *arg0, ...);
extern int execvp(const char *path, char **argv);
extern void _exit(int status);
extern int sbrk(int inc);
extern int dup(int fd);
extern int dup2(int fd, int fd2);
extern int chdir(char *dirname);
extern int close(int fd);
extern int lseek(int fd, long off, int where);
extern int mkdir(char *name, mode_t mode);
extern int rmdir(char *name);
extern int link(const char *name, const char *newname);
extern int sync(void);
extern int unlink(const char *name);
extern int mknod(char *name, mode_t mode, dev_t dev);
extern int execvpe(char * file, char ** argv, char ** envp);
extern int pipe(int fd[2]);
extern int mount(char* special, char *target, char* type, int rw_flag);
extern int umount(char* special);
extern int fchdir(int fd);
extern char *getcwd(char *buf, int buflen);
extern int ioctl(int fd, int cmd, ...);

#endif
