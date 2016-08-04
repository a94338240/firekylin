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
