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

#include <firekylin/kernel.h>
#include <firekylin/sched.h>
#include <firekylin/driver.h>
#include <firekylin/tty.h>

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
	struct tty_struct *tty;

	if (MINOR(dev) == 0)
		return -1;

	tty = tty_table[MINOR(dev)];

	switch (cmd) {
	case TCGETS:
		memcpy((char*) arg, (char*) &tty->termios,
				sizeof(struct termios));
		return 0;
	case TCSETS:
		memcpy((char*) &tty->termios, (char*) arg,
				sizeof(struct termios));
		return 0;
	default:
		return -1;
	}
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
