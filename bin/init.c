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
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char *envp[] = { "PATH=/bin:/test", NULL };

char *ttys[] = { "/dev/tty1", "/dev/tty2", "/dev/com1", NULL };

int main(int argc, char **argv)
{
	char **p = ttys;

	while (*p) {
		if (!fork()) {
			close(0);
			close(1);
			close(2);
			setsid();
			if (open(*p, O_RDWR, 0) < 0)
				exit(0);
			dup(0);
			dup(0);
			execve("/bin/sh", NULL, envp);
		}
		p++;
	}

	wait(NULL);
}
