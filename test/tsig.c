#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

__attribute__((__stdcall__)) long signal_handle(int signo ,long retval)
{
	printf("__signo=%d, retval=%x\n",signo,retval);
	return retval;
}

int main(int argc, char *argv[])
{

	printf("set signal handle\n");

	sigact(SIGUSR1, &signal_handle);
	printf("set singal handle ok!\n");
	int j=5;
	while(j--){

		sigsend(getpid(),SIGUSR1);

		for(int i=0;i<0xfffff;i++);

		printf("have send signal\n");
	}
}
