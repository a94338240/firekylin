/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdio.h>
#include <math.h>

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

#define D(x)   (x* M_PI /180.0)

int main(void)
{
	double i, j;
	int p;
	printf("\nmodf :");
	j = modf(100.123, &i);
	print_f(i);
	print_f(j);
	j = modf(100.00, &i);
	print_f(i);
	print_f(j);
	j = modf(0.123, &i);
	print_f(i);
	print_f(j);

	printf("\nfrexp :");
	j = frexp(100.123, &p);
	printf("%d  ",p);
	print_f(j);
	print_f(ldexp(j,p));
	j = frexp(100.00, &p);
	printf("%d  ",p);
	print_f(j);
	print_f(ldexp(j,p));
	j = frexp(0.123, &p);
	printf("%d  ",p);
	print_f(j);
	print_f(ldexp(j,p));

	return 0;
}
