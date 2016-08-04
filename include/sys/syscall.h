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

#ifndef _SYS_SYSCALL_H
#define _SYS_SYSCALL_H

/* syscall index */
enum {
	__NR_fork,
	__NR_execve,
	__NR_sbrk,
	__NR_waitpid,
	__NR_exit,
	__NR_trace,
	__NR_alarm,
	__NR_times,
	__NR_getpid,
	__NR_setgrp,
	__NR_setsid,
	__NR_getuid,
	__NR_setuid,
	__NR_getgid,
	__NR_setgid,
	__NR_access,
	__NR_open,
	__NR_read,
	__NR_write,
	__NR_close,
	__NR_lseek,
	__NR_fcntl,
	__NR_ioctl,
	__NR_pipe,
	__NR_mknod,
	__NR_mkdir,
	__NR_link,
	__NR_rename,
	__NR_unlink,
	__NR_rmdir,
	__NR_chdir,
	__NR_mount,
	__NR_umount,
	__NR_stat,
	__NR_fstat,
	__NR_chmod,
	__NR_chown,
	__NR_utime,
	__NR_sync,
	__NR_gettimeofday,
	__NR_settimeofday,
	__NR_sigsend,
	__NR_sigmask,
	__NR_sigact,
	__NR_pause,
	__NR_fchdir,
};

#define __syscall0(type,name) 			\
type name(void)					\
{						\
	long res;				\
	__asm__("int $0x30"			\
	    :"=a"(res)				\
	    :"a"(__NR_##name));			\
	if(res<0){				\
		errno=-res;			\
		return (type)(-1);		\
	}					\
	return (type)res;			\
}

#define __syscall1(type,name,typeb,argb) 	\
type name(typeb argb)				\
{						\
	long res;				\
	__asm__("int $0x30"			\
	    :"=a"(res)				\
	    :"a"(__NR_##name),"b"(argb));	\
	if(res<0){				\
		errno=-res;			\
		return (type)(-1);		\
	}					\
	return (type)res;			\
}

#define __syscall2(type,name,typeb,argb,typec,argc) 	\
type name(typeb argb,typec argc)			\
{							\
	long res;					\
	__asm__("int $0x30"				\
	    :"=a"(res)					\
	    :"a"(__NR_##name),"b"(argb),"c"(argc));	\
	if(res<0){					\
		errno=-res;				\
		return (type)(-1);			\
	}						\
	return (type)res;				\
}

#define __syscall3(type,name,typeb,argb,typec,argc,typed,argd) 	\
type name(typeb argb,typec argc,typed argd)			\
{								\
	long res;						\
	__asm__("int $0x30"					\
	    :"=a"(res)						\
	    :"a"(__NR_##name),"b"(argb),"c"(argc),"d"(argd));	\
	if(res<0){						\
		errno=-res;					\
		return (type)(-1);				\
	}							\
	return (type)res;					\
}

#define __syscall4(type,name,typeb,argb,typec,argc,typed,argd,typee,arge) \
type name(typeb argb,typec argc,typed argd,typee arge)			  \
{								          \
	long res;						          \
	__asm__("int $0x30"					          \
	    :"=a"(res)						          \
	    :"a"(__NR_##name),"b"(argb),"c"(argc),"d"(argd),"D"(arge));	  \
	if(res<0){						          \
		errno=-res;					          \
		return (type)(-1);				          \
	}							          \
	return (type)res;					          \
}

#endif
