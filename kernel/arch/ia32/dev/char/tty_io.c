/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <kernel.h>
#include <sched.h>
#include <driver.h>
#include <tty.h>

extern void con_init(void);
extern void kbd_init(void);
extern void com_init(void);

struct tty_struct *tty_table[MAX_TTY];

void copy_to_cook(struct tty_struct *tty)
{
	char ch;
	while (!isempty(&(tty->raw))) {

		/*
		 * get a raw code
		 */
		ch = GETCH(&(tty->raw));

		/*
		 * cook raw code
		 */
		PUTCH(&(tty->cook), ch);

		/*
		 * echo
		 */
		if (tty->termios.c_lflag & ECHO) {
			/*
			 * if buffer is full or '\n' is detected
			 * then flush the line-buffer to the out-buffer
			 * and reset the line-buffer to recieve the
			 * buffer again
			 */
			if (isfull(&(tty->lbuf)) || ch == '\n') {
				/*
				 * flush the line-buffer
				 */

				/*
				 * reset the line-buffer
				 */
				CLRBUF(&(tty->lbuf));

				PUTCH(&(tty->out), ch);
				tty->write(tty);

				wake_up(&(tty->cook.wait));

				continue;

			} else if ('\b' == ch) {
				if (isempty(&(tty->lbuf))) {
					/*
					 * can not backspace now
					 */
					return;
				} else {
					GETCH(&(tty->lbuf));
				}
			} else {
				PUTCH(&(tty->lbuf), ch);
			}
			/*
			 * normal mode
			 */
			PUTCH(&(tty->out), ch);
			tty->write(tty);
		}
		wake_up(&(tty->cook.wait));
	}
}

static int tty_read(dev_t dev, char * buf, off_t off, size_t size)
{
	struct tty_struct *tty;
	long left = size;
	int ch;
	unsigned char scode = 0;

	if (MINOR(dev) == 0) {
		printk("read from tty0");
		return -1;
	}

	tty = tty_table[MINOR(dev)];

	//irq_lock();
	while (left) {
		if (!isempty(&(tty->cook))) {
			ch = GETCH(&(tty->cook));
			*buf++ = ch;
			if (ch == '\n') {
				//irq_unlock();
				return size - left + 1;
			}
			if (ch == C('D')) {
				//irq_unlock();
				return size - left;
			}
			left--;
			continue;
		}
		sleep_on(&(tty->cook.wait), TASK_STATE_BLOCK);
	}
	//irq_unlock();
	return size - left;

}

static int tty_write(dev_t dev, char * buf, off_t off, size_t size)
{
	struct tty_struct *tty;
	long left = size;
	char ch;

	if (MINOR(dev) == 0)
		return -1;

	tty = tty_table[MINOR(dev)];

	while (left) {
		if (!isfull(&(tty->out))) {
			ch = *buf++;
			if (ch == '\n' && (tty->termios.c_oflag & ONLCR))
				PUTCH(&(tty->out), '\r');
			PUTCH(&(tty->out), ch);
			left--;
			continue;
		}
		tty->write(tty);
	}
	tty->write(tty);
	return size - left;
}

static int tty_ioctl(dev_t dev, int cmd, long arg)
{
	return -1;
}

static struct char_device tty =
	{ "TTY", NULL, NULL, tty_read, tty_write, tty_ioctl };

void tty_init(void)
{
	con_init();
	kbd_init();
	com_init();
	char_table[DEV_CHAR_TTY] = &tty;
}
