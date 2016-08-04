/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _STRING_H
#define _STRING_H

#include <sys/types.h>

extern void*  memchr(const void *s, int c, size_t n);
extern int    memcmp(const void *s1, const void *s2, size_t n);
extern void*  memset(void *s, int c, size_t n);
extern void*  memcpy(void *dst, const void *src, size_t n);
extern void*  memmove(void *s1, const void *s2, size_t n);

extern size_t strlen(const char *s);
extern char*  strcat(char *s1, const char *s2);
extern char*  strcpy(char *dst,const char *src);
extern int    strcmp(const char *s1, const char *s2);
extern int    stricmp(const char *s1, const char *s2);

extern size_t strnlen(const char *s, size_t n);
extern char*  strncat(char *s1, const char *s2, size_t n);
extern char*  strncpy(char *dst, const char *src, size_t n);
extern int    strncmp(const char *s1, const char *s2, size_t n);
extern int    strnicmp(const char *s1, const char *s2, size_t n);

extern char*  strchr(const char *s, int c);
extern char*  strrchr(const char *s, int c);
extern char*  strstr(const char *s1, const char *s2);

extern char*  strerror(int errno);

extern char * strpbrk(const char *s1, const char *s2);
extern size_t strcspn(const char *s1, const char *s2);
extern size_t strspn(const char *s1, const char *s2);
extern int    strcoll(const char *s1, const char *s2);
extern char * strtok(char *string, const char *separators);
extern size_t strxfrm(char *s1, const char *save, size_t n);

#endif
