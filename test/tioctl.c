#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/termios.h>
#include <stdio.h>

int main(void)
{
	struct termios term;
	int fd;

	char *ttys[] = { "/dev/tty1", "/dev/com1", NULL };
	char **p = ttys;

	for (p = ttys; *p; p++) {
		fd = open(*p, O_RDWR);
		if (fd < 0)
			continue;
		if (ioctl(fd, TCGETS, &term) < 0)
			continue;
		printf("%s\n", *p);
		printf("%#x,%#x,%#x", term.c_iflag, term.c_oflag, term.c_lflag);
		close(fd);
	}
}
