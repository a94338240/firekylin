/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <firekylin/kernel.h>
#include <ctype.h>
#include <stdarg.h>

#define F_ZEROPAD	0x01
#define F_SIGN		0x02
#define F_PLUS		0x04
#define F_SPACE		0x08
#define F_LEFT		0x10
#define F_SPECIAL	0x20

static char *i_format(char *str, int num, int base, int width, int prec,
		int flag)
{
	char c, sign, tmp[36];
	int i;
	char *digits="0123456789ABCDEF";
	unsigned int u_num;

	if (flag & F_LEFT)
		flag &= ~F_ZEROPAD;
	c = (flag & F_ZEROPAD) ? '0' : ' ';

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
			*str++ = 'x';
		}
	}
	if (!(flag&F_LEFT))
		while(width-->0)
			*str++ = c;
	while(i-->0)
		*str++ = tmp[i];
	while(width-->0)
		*str++ = ' ';
	return str;
}

int vsprintf(char *buf, char *fmt, va_list arg)
{
	int flag, width, prec;
	char *s,*str = buf;
	int len;

	while (*fmt) {
		if (*fmt != '%') {
			*str++ = *fmt++;
			continue;
		}
	        /* get flag */
		flag = 0;
	repeat1:
		fmt++;
		switch (*fmt) {
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
		if (isdigit(*fmt)){
			width=0;
			do{
				width=width*10+*fmt-'0';
				fmt++;
			}while(isdigit(*fmt));
		}
		else if (*fmt == '*') { /* it's the next argument */
			fmt++;
			width = va_arg(arg, int);
			if (width < 0) {
				width = -width;
				flag |= F_LEFT;
			}
		}

		prec=-1;

		/* get conv */
		switch(*fmt++){
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
			if (!(flag & F_LEFT))
				while (len < width--)
					*str++ = ' ';
				for (int i = 0; i < len; ++i)
					*str++ = *s++;
				while (len < width--)
					*str++ = ' ';
			break;

		case 'x':
			str = i_format(str, va_arg(arg, unsigned long), 16,
					width, prec, flag);
			break;

		case 'd':
			flag |=F_SIGN;
			str = i_format(str, va_arg(arg, unsigned long), 10,
					width, prec, flag);
			break;
		default:
			*str++=*(fmt-1);
		}
	}
	return (int)(str-buf);
}
