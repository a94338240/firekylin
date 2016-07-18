#include <stdio.h>
#include <stdlib.h>

void print_f(double x)
{
	long i, j = 6;
	long p;

	i = (long) x;
	printf("%d.", i);
	x = x - i;
	while (j--) {
		x *= 10;
		p = (long) (x);
		x = x - p;
		printf("%d", p);
	}
	printf("   ");
}

int main(void)
{
	char *s1="   123435454pr435";
	char *s2=" 243123.342423p2343233 32423";
	char *s3="  .12234243 e324";

	print_f(strtod(s1,NULL));
	print_f(strtod(s2,NULL));
	print_f(strtod(s3,NULL));

}
