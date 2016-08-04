/* time - time a command	Authors: Andy Tanenbaum & Michiel Huisjes */

/*
 * port for Firekylin by Liuxiaofeng.
 */

#include <sys/types.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <signal.h>

int digit_seen;
char a[] = "        . \0";

void twin(int n, char *p)
{
	char c1, c2;
	c1 = (n / 10) + '0';
	c2 = (n % 10) + '0';
	if (digit_seen == 0 && c1 == '0')
		c1 = ' ';
	*p++ = c1;
	*p++ = c2;
	if (n > 0)
		digit_seen = 1;
}

/* Print the time 't' in hours: minutes: seconds.  't' is in ticks. */
void print_time(clock_t t)
{
	int hours, minutes, seconds, hundredths, i;

	digit_seen = 0;
	for (i = 0; i < 8; i++)
		a[i] = ' ';
	hours = (int) (t / ((clock_t) 3600 * CLK_TCK));
	t -= (clock_t) hours * 3600 * CLK_TCK;
	minutes = (int) (t / ((clock_t) 60 * CLK_TCK));
	t -= (clock_t) minutes * 60 * CLK_TCK;
	seconds = (int) (t / CLK_TCK);
	t -= (clock_t) seconds * CLK_TCK;
	hundredths = (int) (t * 100 / CLK_TCK);

	if (hours) {
		twin(hours, &a[0]);
		a[2] = ':';
	}
	if (minutes || digit_seen) {
		twin(minutes, &a[3]);
		a[5] = ':';
	}
	if (seconds || digit_seen)
		twin(seconds, &a[6]);
	else
		a[7] = '0';
	a[9] = hundredths / 10 + '0';
	a[10] = hundredths % 10 + '0';

	printf(a);
}

int main(int argc, char **argv)
{
	struct tms pre_buf, post_buf;
	clock_t start_time, end_time;
	int status, pid;

	if (argc == 1)
		exit(0);

	/* Get real time at start of run. */

	start_time = time(NULL);

	/* Fork off child. */
	if ((pid = fork()) < 0) {
		fprintf(stderr, "Cannot fork\n");
		exit(1);
	}
	if (pid == 0){
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "Cannot execute %s\n", argv[1]);
		exit(-1);
	}

	/* Parent is the time program.  Disable interrupts and wait. */
	//signal(SIGINT, SIG_IGN);signal(SIGQUIT, SIG_IGN);

	do {
		times(&pre_buf);
	} while (wait(&status) != pid);

	end_time = time(NULL);

	if ((status & 0377) != 0)
		fprintf(stderr, "Command terminated abnormally.\n");

	times(&post_buf);

	/* Print results. -DNEW enables time on one line to 0.01 sec */
	printf("real ");
	print_time(end_time - start_time);
	printf("\nuser ");
	print_time(post_buf.tms_cutime - pre_buf.tms_cutime);
	printf("\nsys  ");
	print_time(post_buf.tms_cstime - pre_buf.tms_cstime);
	printf("\n");

	return ((status & 0377) ? -1 : (status >> 8));
}
