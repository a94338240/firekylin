#include <stdio.h>
#include <time.h>
#include <sys/times.h>

int main()
{
	struct tms tmstmp;

	times(&tmstmp);
	printf("before:%d,%d,%d,%d clock=%d\n", tmstmp.tms_utime, tmstmp.tms_stime,
			tmstmp.tms_cutime, tmstmp.tms_cstime, clock());

	for (int i = 0; i < 0x100; i++){
		printf("%d\t",i);
		for (int j = 0; j < 0xfffff; j++)
					;
	}

	times(&tmstmp);
	printf("after:%d,%d,%d,%d clock=%d\n", tmstmp.tms_utime, tmstmp.tms_stime,
			tmstmp.tms_cutime, tmstmp.tms_cstime,clock());
}
