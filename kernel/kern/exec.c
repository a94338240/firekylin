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

#include <sys/stat.h>
#include <sys/fcntl.h>
#include <firekylin/kernel.h>
#include <firekylin/mm.h>
#include <firekylin/fs.h>
#include <errno.h>

/* define in file fs/read.c */
extern long exec_load_file(struct file *file, char *buf);

static long count(char **arg)
{
	int count = 0;
	while (*arg++)
		count++;
	return count;
}

static long copy_string(char **sh_arg, char **argv, char **envp)
{
	static char *__arg[] = { NULL };
	static long __base = 0x400FF000;

	int sharg_count;
	int argv_count;
	int envp_count;
	long arg_page;
	char *s, *tmp;
	long *tmpl;

	if (!argv)
		argv = __arg;
	if (!envp)
		envp = __arg;

	sharg_count = count(sh_arg);
	argv_count = count(argv);
	envp_count = count(envp);

	if (sharg_count && argv_count) {
		argv_count--;
		argv++;
	}

	arg_page = __va(get_page());

	tmpl = (long*) arg_page;
	*tmpl++ = sharg_count + argv_count;                        /* argc */
	*tmpl++ = __base + 4 * 3;                                  /* argv */
	*tmpl++ = __base + 4 * (3 + sharg_count + argv_count + 1); /* envp */

	s = (char*) arg_page + 4 * ( sharg_count + argv_count + envp_count + 5);

	while (*sh_arg) {
		*tmpl++ = __base + (long) s - arg_page;
		tmp = *sh_arg;
		while (*tmp) {
			*s++ = *tmp++;
		}
		*s++ = 0;
		sh_arg++;
	}
	while (*argv) {
		*tmpl++ = __base + (long) s - arg_page;
		tmp = *argv;
		while (*tmp) {
			*s++ = *tmp++;
		}
		*s++ = 0;
		argv++;
	}
	*tmpl++ = 0;

	while (*envp) {
		*tmpl++ = __base + (long) s - arg_page;
		tmp = *envp;
		while (*tmp) {
			*s++ = *tmp++;
		}
		*s++ = 0;
		envp++;
	}
	*tmpl++ = 0;

	return __pa(arg_page);
}

long sys_execve(char *filename, char **argv, char **envp)
{
	struct inode *inode;
	struct task * current;
	long entry;
	long arg_page;
	char *buf;
	struct file tmpfile;
	char *sh_arg[16];

	current = CURRENT_TASK();

	if (!(inode = namei(filename, NULL)))
		return -ENOENT;

	if (!S_ISREG(inode->i_mode)) {
		iput(inode);
		return -EACCESS;
	}

	buf = (char*) __va(get_page());

	tmpfile.f_inode = inode;
	tmpfile.f_pos = 0;
	tmpfile.f_mode = O_READ;

	if (inode->i_op->file_read(&tmpfile, buf, 128) < 0) {
		put_page(__pa(buf));
		iput(inode);
		return -EIO;
	}

	sh_arg[0] = NULL;

	if (buf[0] == '#' && buf[1] == '!') {
		memcpy(buf + 1024, buf, 128);
		buf[1024 + 127] = 0;

		char *p = buf + 1024 + 2;
		int i = 0;

		while (*p) {
			while (*p == ' ')
				p++;
			sh_arg[i] = p;
			while (*p != ' ' && *p != '\r' && *p != '\n')
				p++;
			if (*p == '\n' || *p == '\r') {
				*p = 0;
				i++;
				break;
			}
			*p++ = 0;
			i++;
			if (i >= 14)
				break;
		}
		sh_arg[i] = filename;
		sh_arg[i + 1] = NULL;

		iput(inode);
		if (!(inode = namei(sh_arg[0], NULL))) {
			put_page(__pa(buf));
			return -ENOENT;
		}

		if (!S_ISREG(inode->i_mode)) {
			put_page(__pa(buf));
			iput(inode);
			return -EACCESS;
		}

		tmpfile.f_inode = inode;
		tmpfile.f_pos = 0;
		tmpfile.f_mode = O_READ;

		if (inode->i_op->file_read(&tmpfile, buf, 128) < 0) {
			put_page(__pa(buf));
			iput(inode);
			return -EIO;
		}
	}

	if (!strncmp(buf, "\0x7FELF", 4)) {
		put_page(__pa(buf));
		iput(inode);
		return -ENOEXEC;
	}

	arg_page = copy_string(sh_arg, argv, envp);

	free_mm();

	entry = exec_load_file(&tmpfile, buf);
	put_page(__pa(buf));
	iput(inode);

	map_page(0x40100000 - 4096, arg_page, current->pdtr);

	current->stack = 0x40FF0000;

	__asm__ (
		" fninit; "
		" movl  %%eax,%%cr3;"
		" pushl $0x23;"
		" pushl $0x400FF000;"
		" pushl $0x13200;"
		" pushl $0x1b;"
		" pushl %%ebx;"
		" iret"
		::"a"(current->pdtr), "b"(entry));

	return 0;
}
