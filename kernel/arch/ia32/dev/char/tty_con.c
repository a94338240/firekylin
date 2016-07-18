/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <lock.h>
#include <tty.h>
#include <ctype.h>
#include <arch/ia32/portio.h>

struct console {
	unsigned long base;
	unsigned long origin;
	unsigned char x;
	unsigned char y;
	unsigned char color;
};

static struct console con_table[MAX_CON];
static struct tty_struct con_tty[MAX_CON];

unsigned int fg_console;
unsigned int cur_console;

#define base	(con_table[cur_console].base)
#define origin	(con_table[cur_console].origin)
#define x	(con_table[cur_console].x)
#define y	(con_table[cur_console].y)
#define color	(con_table[cur_console].color)

static void srcup()
{
	if (y < 25)
		return;
	memcpy((char*) base, (char*) base + 160, 80 * 24 * 2);
	memset((char*) base + 80 * 24 * 2, 0, 80 * 2);
	y = 24;
}

static void write_char(char ch)
{
	char *p = (char*) ( base + (y * 80 + x) * 2);
	if (ch == '\r')
		return;
	if (ch == '\b') {
		if (x > 0) {
			/*
			 * can backspace *
			 */
			x--;
		} else {
			/*
			 * reach the edge
			 * line up
			 */
			if (y > 0) {
				x = 80 - 1;
				y--;
			}
		}

		/*
		 * replace with ' '
		 */
		*--p = color;
		*--p = ' ';

	} else if (ch == '\t') {
		do {
			*p++ = ' ';
			*p++ = color;
		} while (++x % 8);
	} else if (ch == '\n') {
		y++;
		x = 0;
		srcup();
	} else {
		*p++ = ch;
		*p++ = color;
		x++;
		if (x >= 80) {
			x = 0;
			y++;
			srcup();
		}
	}
}

static void cls()
{
	int i = x, j = y;
	for (x = i; x < 80; x++) {
		for (y = j; y < 24; j++)
			write_char(' ');
	}
	x = i, y = j;
}

static void set_orign(void)
{
	outb(0x3d4, 12);
	outb(0x3d5, (base - 0xc00b8000) >> 9 & 0xff);
	outb(0x3d4, 13);
	outb(0x3d5, (base - 0xc00b8000) >> 1 & 0xff);
}

static void set_cur(void)
{
	outb(0x3d4, 14);
	outb(0x3d5, ((base + (y * 80 + x) * 2 - 0xc00b8000) >> 9) & 0xff);
	outb(0x3d4, 15);
	outb(0x3d5, (base + (y * 80 + x) * 2 - 0xc00b8000) >> 1 & 0xff);
}

static int con_write(struct tty_struct *tty)
{
	char ch;
	int res = 0;
	cur_console = tty->private;
	int p1 = 0, p2 = 0, e_esc = 0;

	irq_lock();

	while (!isempty(&(tty->out))) {
		ch = GETCH(&(tty->out));
		switch (e_esc) {
		case 0:
			if (ch == '\033') {
				e_esc = 1;
				continue;
			}
			write_char(ch);
			break;
		case 1:
			if (ch == '[') {
				e_esc = 2;
				p1 = 0;
				continue;
			}
			e_esc = 0;
			write_char(ch);
			break;
		case 2:
			if (isdigit(ch)) {
				p1 = p1 * 10 + ch - '0';
				continue;
			}
			if (ch == ';') {
				e_esc = 3;
				p2 = 0;
				continue;
			}
			if (ch == 'J') {
				e_esc = 0;
				cls();
				continue;
			}
			if (ch == 'E') {
				tty->termios.c_lflag &= ~ECHO;
				e_esc = 0;
				continue;
			}
			e_esc = 0;
			write_char(ch);
			break;
		case 3:
			if (isdigit(ch)) {
				p2 = p2 * 10 + ch - '0';
				continue;
			}
			if (ch == 'H') {
				x = p2 - 1, y = p1 - 1;
				e_esc = 0;
				continue;
			}
			e_esc = 0;
			write_char(ch);
			break;
		}
		res++;
	}
	if (fg_console == cur_console)
		set_cur();
	irq_unlock();
	return res;
}

void select_con(int con)
{
	if (fg_console == con)
		return;
	fg_console = con;
	cur_console = con;
	set_orign();
	set_cur();
}

void con_init()
{
	for (int cur_console = 0; cur_console < MAX_CON; cur_console++) {
		origin = base = 0xc00b8000 + 25 * 80 * 2 * cur_console;
		color = 7;

		memset((void *) &con_tty[cur_console], 0,
				sizeof(con_tty[cur_console]));
		tty_table[cur_console + 1] = &con_tty[cur_console];

		//printk ("count = %d \n",tty_table [cur_console + 1]->kbq.count);

		con_tty[cur_console].write = &con_write;
		con_tty[cur_console].private = cur_console;
		con_tty[cur_console].termios.c_lflag = ECHO;
	}
}

void con_print(char *buf, int len)
{
	cur_console = fg_console;
	while (len--)
		write_char(*buf++);
	set_cur();
}
