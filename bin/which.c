/* which - search paths for executable */

/*
 * port for Firekylin by Liuxiaofeng.
 */

#include <sys/types.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DELIMITER ':'

int main(int argc, char **argv)
{
	char *path, *cp;
	char buf[400];
	char prog[400];
	char patbuf[512];
	int quit, none;
	int excode = 0;

	if (argc < 2) {
		fprintf(stderr, "Usage: which cmd [cmd, ..]\n");
		exit(1);
	}

	for (argv++; *argv; argv++) {
		quit = 0;
		none = 1;
		if ((path = getenv("PATH")) == NULL) {
			fprintf(stderr, "Null path.\n");
			exit(0);
		}
		strcpy(patbuf, path);
		path = patbuf;
		cp = path;

		while (1) {
			cp = strchr(path, DELIMITER);
			if (cp == NULL)
				quit++;
			else
				*cp = '\0';

			if (strcmp(path, "") == 0 && quit == 0) {
				sprintf(buf, "%s./%s", path, *argv);
			} else
				sprintf(buf, "%s/%s", path, *argv);

			path = ++cp;

			if (access(buf, 1) == 0) {
				printf("%s\n", buf);
				none = 0;
			}
			sprintf(prog, "%s.%s", buf, "prg");
			if (access(prog, 1) == 0) {
				printf("%s\n", prog);
				none = 0;
			}
			sprintf(prog, "%s.%s", buf, "ttp");
			if (access(prog, 1) == 0) {
				printf("%s\n", prog);
				none = 0;
			}
			sprintf(prog, "%s.%s", buf, "tos");
			if (access(prog, 1) == 0) {
				printf("%s\n", prog);
				none = 0;
			}
			if (quit) {
				if (none) {
					fprintf(stderr, "No %s in %s\n", *argv,
							getenv("PATH"));
					excode = 1;
				}
				break;
			}
		}
	}
	return (excode);
}
