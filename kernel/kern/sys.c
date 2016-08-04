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

#include <sys/syscall.h>

extern long sys_fork();
extern long sys_execve();
extern long sys_sbrk();
extern long sys_waitpid();
extern long sys_exit();
extern long sys_trace();
extern long sys_alarm();
extern long sys_times();
extern long sys_getpid();
extern long sys_setgrp();
extern long sys_setsid();
extern long sys_getuid();
extern long sys_setuid();
extern long sys_getgid();
extern long sys_setgid();
extern long sys_access();
extern long sys_open();
extern long sys_read();
extern long sys_write();
extern long sys_close();
extern long sys_lseek();
extern long sys_fcntl();
extern long sys_ioctl();
extern long sys_pipe();
extern long sys_mknod();
extern long sys_mkdir();
extern long sys_link();
extern long sys_rename();
extern long sys_unlink();
extern long sys_rmdir();
extern long sys_chdir();
extern long sys_mount();
extern long sys_umount();
extern long sys_stat();
extern long sys_fstat();
extern long sys_chmod();
extern long sys_chown();
extern long sys_utime();
extern long sys_sync();
extern long sys_gettimeofday();
extern long sys_settimeofday();
extern long sys_sigsend();
extern long sys_sigmask();
extern long sys_sigact();
extern long sys_pause();
extern long sys_fchdir();

long (*syscall_table[])()= {
	sys_fork,
	sys_execve,
	sys_sbrk,
	sys_waitpid,
	sys_exit,
	sys_trace,
	sys_alarm,
	sys_times,
	sys_getpid,
	sys_setgrp,
	sys_setsid,
	sys_getuid,
	sys_setuid,
	sys_getgid,
	sys_setgid,
	sys_access,
	sys_open,
	sys_read,
	sys_write,
	sys_close,
	sys_lseek,
	sys_fcntl,
	sys_ioctl,
	sys_pipe,
	sys_mknod,
	sys_mkdir,
	sys_link,
	sys_rename,
	sys_unlink,
	sys_rmdir,
	sys_chdir,
	sys_mount,
	sys_umount,
	sys_stat,
	sys_fstat,
	sys_chmod,
	sys_chown,
	sys_utime,
	sys_sync,
	sys_gettimeofday,
	sys_settimeofday,
	sys_sigsend,
	sys_sigmask,
	sys_sigact,
	sys_pause,
	sys_fchdir,
};
