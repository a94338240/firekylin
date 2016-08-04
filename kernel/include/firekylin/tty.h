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

#ifndef _TTY_H
#define _TTY_H

#include <firekylin/sched.h>
#include <firekylin/keys.h>
#include <termios.h>

#define C(x) (x - '@')

#define MAX_CON		3	/* max vitrual console 	*/
#define MAX_COM		2	/* max rs232		*/

#define MAX_TTY		(1+MAX_CON+MAX_COM)

#define TTY_BUF_SIZE 1024
struct tty_buf {
	char             buf[TTY_BUF_SIZE];
	unsigned short   head;
	unsigned short   tail;
	unsigned short   count;
	unsigned short   lines;
	struct task  *   wait;
};

struct tty_struct {
	struct termios  termios;
	unsigned int    pgrp;
	struct tty_buf  kbq;		/* keyboard scan code queue */
	struct tty_buf  raw;
	struct tty_buf  cook;
	struct tty_buf  out;
	struct tty_buf  lbuf;		/* line buffer */
	int             (*write)(struct tty_struct *tty);
	unsigned long   private;
};

static inline int isfull(struct tty_buf *buf)
{
	return buf->count==TTY_BUF_SIZE;
}

static inline int isempty(struct tty_buf *buf)
{
	return buf->count == 0;
}

static inline int GETCH(struct tty_buf *buf)
{
	char retval;
	if (isempty (buf))
		return (-1);
	retval=buf->buf[buf->tail];
	buf->tail=(buf->tail +1)% TTY_BUF_SIZE;
	buf->count--;
	return retval;
}

/* peek a queued char ,but not deque */
static inline int PEEKCH(struct tty_buf *buf) 
{
	char retval;
	if (isempty (buf))
		return (-1);
	retval=buf->buf[buf->tail];
	return retval;
}

static inline void PUTCH(struct tty_buf *buf,char ch)
{
	buf->buf[buf->head]=ch;
	buf->count++;
	buf->head=(buf->head +1)% TTY_BUF_SIZE;
}

static inline void CLRBUF(struct tty_buf *buf)
{
	if (buf) {
		buf->head = 0;
		buf->tail = 0;
		buf->count = 0;
	}
}

extern struct tty_struct *tty_table[MAX_TTY];
extern unsigned int fg_console;
extern void copy_to_cook(struct tty_struct *tty);

#endif
