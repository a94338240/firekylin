/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SYS_SYSCALL_H
#define _SYS_SYSCALL_H

/* syscall index */
enum {
	__NR_fork,
	__NR_execve,
	__NR_sbrk,
	__NR_wait,
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
	__NR_getime,
	__NR_setime,
	__NR_sigsend,
	__NR_sigmask,
	__NR_sigact,
	__NR_pause,
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
