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
 
#ifndef _WCHAR_H
#define _WCHAR_H

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <wctype.h>

wint_t   btowc(int);
size_t   mbrlen(const char *, size_t, mbstate_t *);
size_t   mbrtowc(wchar_t *, const char *, size_t, mbstate_t *);
int      mbsinit(const mbstate_t *);
size_t   mbsrtowcs(wchar_t *, const char **, size_t, mbstate_t *);
size_t   wcrtomb(char *, wchar_t, mbstate_t *);
wchar_t *wcscat(wchar_t *, const wchar_t *);
wchar_t *wcschr(const wchar_t *, wchar_t);
int      wcscmp(const wchar_t *, const wchar_t *);
int      wcscoll(const wchar_t *, const wchar_t *);
wchar_t *wcscpy(wchar_t *, const wchar_t *);
size_t   wcscspn(const wchar_t *, const wchar_t *);
size_t   wcsftime(wchar_t *, size_t, const wchar_t *, const struct tm *);
size_t   wcslen(const wchar_t *);
wchar_t *wcsncat(wchar_t *, const wchar_t *, size_t);
int      wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t *wcsncpy(wchar_t *, const wchar_t *, size_t);
wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
wchar_t *wcsrchr(const wchar_t *, wchar_t);
size_t   wcsrtombs(char *, const wchar_t **, size_t, mbstate_t *);
size_t   wcsspn(const wchar_t *, const wchar_t *);
wchar_t *wcsstr(const wchar_t *, const wchar_t *);
wchar_t *wcstok(wchar_t *, const wchar_t *, wchar_t **);
size_t   wcsxfrm(wchar_t *, const wchar_t *, size_t);
wchar_t *wcswcs(const wchar_t *, const wchar_t *);
wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);
int      wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t *wmemcpy(wchar_t *, const wchar_t *, size_t);
wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t *wmemset(wchar_t *, wchar_t, size_t);

size_t   wcslcat(wchar_t *, const wchar_t *, size_t);
size_t   wcslcpy(wchar_t *, const wchar_t *, size_t);
int      wcswidth(const wchar_t *, size_t);
int      wctob(wint_t);
int      wcwidth(wchar_t);

unsigned long int wcstoul(const wchar_t *, wchar_t **, int);
long int wcstol(const wchar_t *, wchar_t **, int);
double wcstod(const wchar_t *, wchar_t **);

wint_t   ungetwc(wint_t, FILE *);
wint_t   fgetwc(FILE *);
wchar_t *fgetws(wchar_t *, int, FILE *);
wint_t   getwc(FILE *);
wint_t   getwchar(void);
wint_t   fputwc(wchar_t, FILE *);
int      fputws(const wchar_t *, FILE *);
wint_t   putwc(wchar_t, FILE *);
wint_t   putwchar(wchar_t);

int fwide(FILE *, int);

wchar_t *fgetwln(FILE *, size_t *);
int      fwprintf(FILE *, const wchar_t *, ...);
int      fwscanf(FILE *, const wchar_t *, ...);
int      swprintf(wchar_t *, size_t n, const wchar_t *, ...);
int      swscanf(const wchar_t *, const wchar_t *, ...);
int      vfwprintf(FILE *, const wchar_t *, va_list);
int      vswprintf(wchar_t *, size_t, const wchar_t *, va_list);
int      vwprintf(const wchar_t *, va_list);
int      wprintf(const wchar_t *, ...);
int      wscanf(const wchar_t *, ...);
int      vfwscanf(FILE * , const wchar_t * , va_list);
int      vswscanf(const wchar_t * , const wchar_t * ,va_list);
int      vwscanf(const wchar_t * , va_list);
wchar_t *wcsdup (const wchar_t *);
int      wcsncasecmp (const wchar_t *, const wchar_t *, size_t);
int      wcscasecmp(const wchar_t *, const wchar_t *);

#ifndef WEOF
#define	WEOF 	((wint_t)-1)
#endif

#define getwc(f) 	fgetwc(f)
#define getwchar() 	getwc(stdin)
#define putwc(wc, f) 	fputwc((wc), (f))
#define putwchar(wc) 	putwc((wc), stdout)

#endif /* !_WCHAR_H_ */
