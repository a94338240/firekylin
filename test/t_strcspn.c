/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s1 = "Adcbcrxcw4p08grdffredfddf";
	char *s2 = "acf";
	char *s3 = "g09";

	printf("%d\n", strcspn(s1, s2));
	printf("%d\n", strcspn(s1, s3));

	printf("%d\n", strpbrk(s1, s2) - s1);
	printf("%d\n", strpbrk(s1, s3) - s1);
	char *str = "Linux was first developed for 386/486-based pcs.";
	printf("%d\n", strspn(str, "Linux"));
	printf("%d\n", strspn(str, "/-"));
	printf("%d\n", strspn(str, "1234567890"));
}
