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

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

#define MAX_ARG 64

char *ps1 = "sh>";

struct cmd_struct {
	char *name;
	int (*fun)(int, char **);
};

int do_help(int argc, char **argv)
{
	printf("help information:\n");
	printf("\tcls       clear screen\n");
	printf("\tcd        change current working directory\n");
	printf("\tpwd       print current working directory\n");
	printf("\techo      write arguments to standard output\n");
	printf("\thelp      print this information\n");
	printf("\tls        list directory\n");
	printf("\tcat       concatenate and print files\n");
	printf("\tcp        copy files\n");
	printf("\tmkdir     create dir\n");
	printf("\trmdir     rm empty dir\n");
	return 0;
}

int do_echo(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}

int do_cls(int argc, char **argv)
{
	printf("\033[1;1H");
	for (int i = 0; i < 8 * 24; i++) {
		printf("          ");
	}
	printf("\033[1;1H");
	return 0;
}

int do_cd(int argc, char **argv)
{
	if (argv[1]) {
		chdir(argv[1]);
	} else {
		chdir("/");
	}
	return 0;
}

int do_pwd(int argc, char **argv)
{
	char buf[PATH_MAX + 1];
	printf("%s\n", getcwd(buf, sizeof(buf)));
	return 0;
}

int get_cmd(char *buf, int size)
{
	int i = 0;
	char ch;
	while (1) {
		if (read(0, &ch, 1) < 0) {
			break;
		}
		if (ch == '\n') {
			break;
		}
		if (ch == '\r')
			continue;

		buf[i++] = ch;
		if (i >= size - 1)
			break;
	}

	buf[i] = 0x00;
	buf[size - 1] = 0x00;
	//printf ("in >> %s \n",buf);
	return (i);
}

int parcmd(char *buf, char **argv)
{
	int i;
	for (i = 0; i < MAX_ARG; i++) {
		while (*buf == ' ')
			buf++;
		if (*buf == 0) {
			argv[i] = NULL;
			break;
		}

		argv[i] = buf;

		while (*buf && *buf != ' ')
			buf++;

		if (*buf != 0)
			*buf++ = 0;
	}
	return i;
}

struct cmd_struct builtins[] = {
	{ "cd"  , do_cd    },
	{ "echo", do_echo  },
	{ "cls" , do_cls   },
	{ "help", do_help  },
	{ "pwd" , do_pwd   }
};

int execcmd(int argc, char **argv)
{
	int pid;
	for (int i = 0; i < sizeof(builtins) / sizeof(struct cmd_struct); i++) {
		if (strcmp(argv[0], builtins[i].name) == 0)
			return (*builtins[i].fun)(argc, argv);
	}

	pid = fork();
	if (!pid) {
		execvp(argv[0], argv);
		printf("sh:%s\n", strerror(errno));
		_exit(0);
	}
	wait(NULL);
	return 0;
}

int main(void)
{
	char *argv[MAX_ARG];
	int argc;
	char buf[100];

	//do_cls(0,NULL);

	printf("Welcome To FireKylin !\n");

	while (1) {
		printf("%s", ps1);
		if (get_cmd(buf, sizeof(buf))) {
			argc = parcmd(buf, argv);
			execcmd(argc, argv);
		}
	}
}
