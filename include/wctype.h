/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _WCTYPE_H
#define _WCTYPE_H

#include <ctype.h>

typedef signed long wint_t;

extern int iswupper(int c);
extern int iswlower(wint_t c);
extern int iswdigit(wint_t c);
extern int iswcntrl(wint_t c);
extern int iswspace(wint_t c);
extern int iswpunct(wint_t c);
extern int iswxdigit(wint_t c);
extern int iswalpha(wint_t c);
extern int iswalnum(wint_t c);
extern int iswgraph(wint_t c);
extern int iswprint(wint_t c);
extern int iswascii(wint_t c);
extern wint_t towlower(wint_t c);
extern wint_t towupper(wint_t c);

#define iswupper(c)	(__ctype[(c)+1]&(_U))
#define iswlower(c)	(__ctype[(c)+1]&(_L))
#define iswdigit(c)	(__ctype[(c)+1]&(_D))
#define iswcntrl(c)	(__ctype[(c)+1]&(_C))
#define iswspace(c)	(__ctype[(c)+1]&(_S))
#define iswpunct(c)	(__ctype[(c)+1]&(_P))
#define iswxdigit(c)	(__ctype[(c)+1]&(_D|_X))
#define iswalpha(c)	(__ctype[(c)+1]&(_U|_L))
#define iswalnum(c)	(__ctype[(c)+1]&(_U|_L|_D))
#define iswgraph(c)	(__ctype[(c)+1]&(_P|_U|_L|_D))
#define iswprint(c)	(__ctype[(c)+1]&(_P|_U|_L|_D))
#define iswascii(c)	((c)<=0x7f)

#define towlower(c)	(iswupper(c) ? (c)+0x20 : (c))
#define towupper(c)	(iswlower(c) ? (c)-0x20 : (c))

#endif
