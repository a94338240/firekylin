#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>

int main()
{
	FILE *fp;
	char c;

	fp = fopen("/dev/com1", " ");
	for (int i = 0; i < 10; i++) {
		printf("consloe out:%d\n", i);
		fprintf(fp, "test puts %d\r\n", i);
		fflush(fp);
	}

	for (int i = 0; i < 10; i++) {
		read(fileno(fp), &c, 1);
		printf("read_com:%c,%d\n", c, c);
	}
	fclose(fp);

	fp = fopen("/dev/com2", " ");
	for (int i = 0; i < 10; i++) {
		printf("consloe out:%d\n", i);
		fprintf(fp, "test puts %d\r\n", i);
		fflush(fp);
	}

	for (int i = 0; i < 10; i++) {
		read(fileno(fp), &c, 1);
		printf("read_com:%c,%d\n", c, c);
	}
}
