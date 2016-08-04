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

/************************************************************************
 *
 *     %[flag][width][.prec][mod][conv]
 *	flag:	-	left justify, pad right w/ blanks
 *		0	pad left w/ 0 for numerics
 *		+	always print sign, + or -
 *		' '	(blank)
 *		#	(???)
 *
 *	width:		(field width) / *
 *
 *	prec:		(precision)
 *
 *	mod:	h	short (16-bit) int
 *		l	long (32-bit) int
 *		L	long long (64-bit) int
 *
 *	conv:	d,i	decimal int
 *		u	decimal unsigned
 *		o	octal
 *		x,X	hex
 *		f,e,g,E,G float
 *		c	char
 *		s	string
 *		p	ptr
 *		%       %
 *
 ***************************************************************************/

#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define F_ZEROPAD	1
#define F_SIGN		2
#define F_PLUS		4
#define F_SPACE		8
#define F_LEFT		16
#define F_SPECIAL	32
#define F_SMALL		64

static char *uppers="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char *lowers="0123456789abcdefghijklmnopqrstuvwxyz";

static char *i_format(char *str, int num, int base, int width, int prec,
		int flag)
{
	char c, sign, tmp[36];
	int i;
	char *digits;
	unsigned int u_num;

	if (base < 2 || base > 36)
		return str;
	if (flag & F_LEFT)
		flag &= ~F_ZEROPAD;
	c = (flag & F_ZEROPAD) ? '0' : ' ';
	digits = (flag & F_SMALL) ? lowers : uppers;

	if ((flag&F_SIGN) && num<0) {
		sign='-';
		num = -num;
	} else
		sign=(flag&F_PLUS) ? '+' : ((flag&F_SPACE) ? ' ' : 0);
	if (flag&F_SPECIAL){
		if (base==16)
			width -= 2;
		else if (base==8)
			width--;
	}

	i=0;
	u_num=num;
	do{
		tmp[i++]=digits[u_num%base];
		u_num=u_num/base;
	}while(u_num);

	if (i>prec)
		prec=i;
	width-=prec;
	if (!(flag&(F_ZEROPAD | F_LEFT)))
		while(width-->0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	if (flag&F_SPECIAL){
		if (base==8)
			*str++ = '0';
		else if (base==16) {
			*str++ = '0';
			*str++ = digits[33];
		}
	}
	if (!(flag&F_LEFT))
		while(width-->0)
			*str++ = c;
	while(i<prec--)
		*str++ = '0';
	while(i-->0)
		*str++ = tmp[i];
	while(width-->0)
		*str++ = ' ';
	return str;
}

int vsprintf(char *buf, const char *fmt, va_list arg)
{
	int flag, width, prec;
	char *s,*str = buf;
	int len;
	char *tfmt=(char *)fmt;

	while (*tfmt) {
		if (*tfmt != '%') {
			*str++ = *tfmt++;
			continue;
		}
	        /* get flag */
		flag = 0;
	repeat1:
		tfmt++;
		switch (*tfmt) {
		case '-':
			flag |= F_LEFT;
			goto repeat1;
		case '+':
			flag |= F_PLUS;
			goto repeat1;
		case ' ':
			flag |= F_SPACE;
			goto repeat1;
		case '#':
			flag |= F_SPECIAL;
			goto repeat1;
		case '0':
			flag |= F_ZEROPAD;
			goto repeat1;
		}

		/* get width */
		width=-1;
		if (isdigit(*tfmt)){
			width=0;
			do{
				width=width*10+*tfmt-'0';
				tfmt++;
			}while(isdigit(*tfmt));
		}
		else if (*tfmt == '*') { /* it's the next argument */
			tfmt++;
			width = va_arg(arg, int);
			if (width < 0) {
				width = -width;
				flag |= F_LEFT;
			}
		}

		/*get prec */
		prec=-1;
		if (*tfmt == '.') {
			tfmt++;
			if (isdigit(*tfmt)){
				prec=0;
				do{
					prec=prec*10+*tfmt-'0';
					tfmt++;
				}while(isdigit(*tfmt));
			}
			else if (*tfmt == '*') { /* it's the next argument */
				prec = va_arg(arg, int);
				if (prec < 0)
					prec = 0;
			}
		}

		/* get mod */
		//mod=-1;
		if (*tfmt == 'h' || *tfmt == 'l' || *tfmt == 'L')
			//mod = *tfmt++;
			tfmt++;

		/* get conv */
		switch(*tfmt++){
		case '%':
			if (!(flag & F_LEFT))
				while (--width > 0)
					*str++ = ' ';
			*str++ ='%';
			while (--width > 0)
				*str++ = ' ';
			break;
		case 'c':
			if (!(flag & F_LEFT))
				while (--width > 0)
					*str++ = ' ';
			*str++ = (unsigned char) va_arg(arg, int);
			while (--width > 0)
				*str++ = ' ';
			break;

		case 's':
			s = va_arg(arg, char *);
			len = strlen(s);
			if (prec < 0)
				prec = len;
			else if (len > prec)
				len = prec;
			if (!(flag & F_LEFT))
				while (len < width--)
					*str++ = ' ';
				for (int i = 0; i < len; ++i)
					*str++ = *s++;
				while (len < width--)
					*str++ = ' ';
			break;

		case 'o':
			str = i_format(str, va_arg(arg, unsigned long), 8,
					width, prec, flag);
			break;

		case 'p':
			if (width == -1) {
				width = 8;
				flag |= F_ZEROPAD;
			}
			str = i_format(str, (long) (va_arg(arg, void*)), 16,
					width, prec, flag);
			break;

		case 'x':
			flag |= F_SMALL;
		case 'X':
			str = i_format(str, va_arg(arg, unsigned long), 16,
					width, prec, flag);
			break;

		case 'd':
		case 'i':
			flag |=F_SIGN;
		case 'u':
			str = i_format(str, va_arg(arg, unsigned long), 10,
					width, prec, flag);
			break;
		default:
			*str++=*(tfmt-1);
		}
	}
	return (int)(str-buf);
}
