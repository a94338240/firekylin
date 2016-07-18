/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/types.h>

typedef struct {
	int quot;
	int rem;
} div_t;

typedef struct {
	long quot;
	long rem;
} ldiv_t;

extern char **environ;

extern int    abs(int i);
extern void * malloc(long nbytes);
extern void * realloc(void *ptr, size_t size);
extern void * calloc(size_t nelem, size_t elsize);
extern void   free(void *p);
extern char * getenv(const char *name);
extern void   exit(int exit_code);
extern int  rand(void);
extern void srand(unsigned int seed);

extern long strtol(const char *str, char **endptr, int base);
extern long long strtoll(const char *str, char **endptr, int base);
extern unsigned long strtoul(const char *str, char **endptr, int base);
extern unsigned long long strtoull(const char *str, char **endptr, int base);

extern float strtof(const char *ptr, char **endptr);
extern double strtod(const char *ptr, char **endptr);
extern long double strtold(const char *ptr, char **endptr);

extern void abort(void);
extern int atoi(const char *s);
extern long atol(const char *s);

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1

static inline int system(const char *cmd)
{
	return -1;
}

#endif
